# leveldb::SkipList
## SkipList::Node基本参数
```c++
    template<typename Key, class Comparator>
    struct SkipList<Key,Comparator>::Node
```
- `Key const key` - 保证跳表节点按key排序
- `port::AtomicPointer next_[1]` - next指针数组，默认高度为1，实际高度由随机化函数计算

## SkipList基本参数
```c++
    template<typename Key, class Comparator>
    class SkipList
```
- `Comparator const compare_` - key比较函数
- `Arena* const arena_` - 使用arena为节点分配内存
- `Node* const head_` - 跳表头部节点
- `port::AtomicPointer max_height_` - 跳表的高度，所有节点高度的最大值
- `Random rnd_` - 随机化函数，决定节点的高度

## SkipList::RandomHeight() - 节点分层
- `kMaxHeight = 12` - 节点最大高度，也是跳表最大高度
- `static const unsigned int kBranching = 4` - 节点高度每增加1的概率为1/4
```
节点层数概率：
P(h=1) = 3/4
P(h=2) = 1/4 * 3/4
P(h=3) = 1/(4^2) * 3/4
P(h=11) = 1/(4^10) * 3/4
P(h=12) = 1/(4^11)
节点层数期望：
E(h) = 3/4 * 1 + 1/4 * 3/4 * 2 + ... + 1/(4^10) * 3/4 * 11 + 1/(4^11) * 12 = 4/3
空间开销分析：
记每个链表节点携带next指针的空间开销为1，则每个跳表节点携带next_指针数组的空间开销为1.33
```

## SkipList::Insert(const Key& key) - 节点插入
- 查找插入位置
```c++
    SkipList<Key,Comparator>::Node*
    SkipList<Key,Comparator>::FindGreaterOrEqual(const Key& key, Node** prev) {
        Node* x = head_;
        int level = GetMaxHeight() - 1; // 从跳表的最上层开始查找，上层节点数少，下层节点数多
        while (true) {
            Node* next = x->Next(level);
            if (KeyIsAfterNode(key, next)) {
                // Keep searching in this list，在跳表的当前层查找插入位置: prev[level]
                x = next;
            } else {
                if (prev != nullptr) prev[level] = x;
                if (level == 0) {
                    return next;
                } else {
                    // Switch to next list，在跳表的下一层继续查找插入位置: prev[level-1]
                    level--;
                }
            }
        }
    }
```
- 节点分层
```c++
    int height = RandomHeight();
    
    // 新增节点的高度超过跳表高度max_height_
    if (height > GetMaxHeight()) {
        for (int i = GetMaxHeight(); i < height; i++) {
            prev[i] = head_; // 超过max_height_的部分，prev就是head节点
        }
        
        // 更新跳表高度: max_height_ = height
        max_height_.NoBarrier_Store(reinterpret_cast<void*>(height));
    }
```
- 创建node，并执行类似链表节点插入的指针连接操作
```c++
    x = NewNode(key, height);
    for (int i = 0; i < height; i++) {
        // 将node.level[i].next依次连接到prev[i].level[i].next
        x->NoBarrier_SetNext(i, prev[i]->NoBarrier_Next(i));
        
        // 将prev[i].level[i].next依次连接到node
        prev[i]->SetNext(i, x);
    }
    
    SkipList<Key,Comparator>::NewNode(const Key& key, int height) {
        // 使用arena为node分配内存，node.next_指针数组的高度由随机化函数计算
        char* mem = arena_->AllocateAligned(sizeof(Node) + sizeof(AtomicPointer) * (height-1));
        
        // placement new
        return new (mem) Node(key);
    }
```

## SkipList复杂度分析
```
T.节点插入 = T.节点删除 = T.查找插入位置
T.查找插入位置 = 从head最左最高处出发，向右向下依次遍历，直到node的查找长度
T.查找插入位置 = 从node出发，向左向上依次回溯，直到head最左最高处的查找长度
记node到head的高度差为k，查找长度期望为C(k)，向上走一步的概率为p，向左走一步的概率为1-p，则有：
C(0) = 0
C(k) = P(向上走一步) * (C(k-1) + 1) + P(向左走一步) * (C(k) + 1)
C(k) = p * C(k-1) + p + (1-p) * C(k) + (1-p)
C(k) = C(k-1) + 1/p
C(k) = k/p
n个节点的跳表高度估计：
第1层节点数：n
第2层节点数期望：n * p
第3层节点数期望：n * p^2
假设跳表最高层节点数为1，则有：n * p^(h-1) = 1，计算得：h = log(1/p)n + 1
复杂度估计：
T.查找插入位置 = C(h-1) = log(1/p)n / p = O(logn)
```

## 参考链接
- https://www.cnblogs.com/xuqiang/archive/2011/05/22/2053516.html
- https://blog.csdn.net/u010412301/article/details/64923131
