# leveldb::Arena
## Arena基本参数
- `static const int kBlockSize = 4096` - 默认内存块大小
- `std::vector<char*> blocks_` - 存放所有内存块的指针
- `char* alloc_ptr_` - 当前内存块空闲起始位置
- `size_t alloc_bytes_remaining_` - 当前内存块剩余大小

## Arena内存分配策略
1. 申请内存大小`bytes` < 当前块剩余大小`alloc_bytes_remaining_`
    - 在当前块上分配，仅需要移动当前块的`alloc_ptr_`指针
2. 当前块剩余大小`alloc_bytes_remaining_` < 申请内存大小`bytes` < 1k
    - 使用`new[]`申请一个大小为4096的内存块，然后移动当前块的`alloc_ptr`指针
    - 注意：在这种情况下，上一个内存块中`alloc_bytes_remaining_`的大小被浪费了
3. 申请内存大小`bytes` > 当前块剩余大小`alloc_bytes_remaining_` && 申请内存大小`bytes` > 1k
    - 使用`new[]`申请一个大小为bytes的内存块，不移动当前块的`alloc_ptr`指针
4. Arena析构时，使用`delete[]`释放`blocks_`持有的所有内存块的指针

## 参考链接
- https://www.jianshu.com/p/f5eebf44dec9
