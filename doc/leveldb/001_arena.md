# leveldb::Arena
## Arena基本参数
- `static const int kBlockSize = 4096` - 默认内存块大小
- `std::vector<char*> blocks_` - 存放所有内存块的指针
- `char* alloc_ptr_` - 当前内存块空闲起始位置
- `size_t alloc_bytes_remaining_` - 当前内存块剩余大小
- `port::AtomicPointer memory_usage_` - 内存用量统计

## Arena::Allocate(size_t bytes) - 内存分配策略
1. `申请内存大小bytes < 当前块剩余大小alloc_bytes_remaining_`
    - 在当前块上分配，仅需要移动当前块的`alloc_ptr_`指针
2. `当前块剩余大小alloc_bytes_remaining_ < 申请内存大小bytes < 1k`
    - 使用`new[]`申请一个大小为4096的内存块，然后移动当前块的`alloc_ptr`指针
    - 注意：在这种情况下，上一个4k内存块中`alloc_bytes_remaining_`的大小被浪费
3. `申请内存大小bytes > 当前块剩余大小alloc_bytes_remaining_ && 申请内存大小bytes > 1k`
    - 使用`new[]`申请一个大小为bytes的内存块，不移动当前块的`alloc_ptr`指针
4. Arena析构时，使用`delete[]`释放`blocks_`持有的所有内存块的指针

```c++
    inline char* Arena::Allocate(size_t bytes) {
        // 当前块剩余大小充足
        if (bytes <= alloc_bytes_remaining_) {
            char* result = alloc_ptr_;
            alloc_ptr_ += bytes;
            alloc_bytes_remaining_ -= bytes;
            return result;
        }
        
        // 当前块剩余大小不足
        return AllocateFallback(bytes);
    }

    char* Arena::AllocateFallback(size_t bytes) {
        if (bytes > kBlockSize / 4) {
            char* result = AllocateNewBlock(bytes); // 超过1k的块单独分配
            return result;
        }

        // 分配一个新的4k块，上一个4k块的剩余大小被浪费
        alloc_ptr_ = AllocateNewBlock(kBlockSize);
        alloc_bytes_remaining_ = kBlockSize;

        // 移动alloc_ptr_指针
        char* result = alloc_ptr_;
        alloc_ptr_ += bytes;
        alloc_bytes_remaining_ -= bytes;
        return result;
    }

    char* Arena::AllocateNewBlock(size_t block_bytes) {
        char* result = new char[block_bytes];
        blocks_.push_back(result);
        
        // 新分配的内存块加入用量统计
        memory_usage_.NoBarrier_Store(reinterpret_cast<void*>(MemoryUsage() +
                                      block_bytes + sizeof(char*)));
        
        return result;
    }
```

## 参考链接
- https://www.jianshu.com/p/f5eebf44dec9
