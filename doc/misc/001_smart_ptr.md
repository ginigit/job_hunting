# C++智能指针
## RAII
RAII: Resource Acquisition Is Initialization - 资源获取即初始化
1. 定义一个类封装资源的分配与释放
2. 在构造函数中完成资源的分配及初始化
3. 在析构函数中完成资源的反初始化和释放
4. RAII的意义：对象离开作用域时调用析构函数，将自动释放资源，保证异常安全性

例子：
- scoped_lock
- smart_pointer

## unique_ptr
1. 独占对象的所有权
    - 不允许拷贝：A(const A& a)，A& operator=(A& a)
    - 不允许多个unique_ptr指向同一个对象
2. 允许移动构造和移动赋值：A(const A&& a)，A& operator=(A&& a)
3. 析构，或变更指向对象时，释放指向对象的内存
    - 使用`unique_ptr.reset()`变更指向对象
    - 使用`unique_ptr.release()`释放指向对象

## shared_ptr
1. 共享对象的所有权
    - 允许拷贝
    - 允许多个shared_ptr指向同一个对象
    - 允许移动
2. 引用计数use_count
    - 引用计数是线程安全的，但不保证指向对象的线程安全性
    - 每拷贝1次，引用计数加1；每析构1次，引用计数减1
    - use_count=0时，释放指向对象的内存
3. 使用`shared_ptr.get()`获取原生指针
4. 使用`shared_ptr.reset()`变更指向对象
5. 循环引用问题：类似死锁的逻辑，ptrA释放对象内存依赖于ptrB，ptrB释放对象内存依赖于ptrA，导致二者都无法释放

```c++
class A
{
public:
    void setPtr(shared_ptr<B>& spb) { m_spb = spb; }
    shared_ptr<B> m_spb;
};
class B
{
public:
    void setPtr(shared_ptr<A>& spa) { m_spa = spa; }
    shared_ptr<A> m_spa;
};
shared_ptr<A> a(new A);
shared_ptr<B> b(new B);
a->setPtr(b);
b->setPtr(a);
// 产生循环引用，使用weak_ptr可以解决此问题
```

## weak_ptr
1. 弱引用特性
    - 不允许基于原生指针构造，只允许基于shared_ptr、weak_ptr构造，通常作为shared_ptr的辅助工具使用
    - 基于shared_ptr构造，不影响shared_ptr的引用计数，也不参与被指向对象的资源管理（不持有对象的所有权）
    - weak_ptr没有重载`operator->`和`operator*`因此无法直接操作被指向对象
2. 使用`weak_ptr.lock()`将weak_ptr转换成shared_ptr，进而操作被指向对象
3. 使用`weak_ptr.expire()`判断shared_ptr指向的对象是否已经被释放
