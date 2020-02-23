# leveldb::Memtable
## Memtable记录格式
```
| internal_key_size |    user_key   | seq_num/type | user_value_size |   user_value    |
|     varint32      | user_key.size |       8      |    varint32     | user_value.size |
```
- `internal_key_size = user_key.size + sizeof(type)` - 内部键长度 = 用户键长度 + 8
- `user_key` - 用户键，即用户调用`DBImpl::Put(options, key, val)`传入的key
- `seq_num/type = seq_num << 8 | type` - 序列号和记录类型，长度 = 8
    - `seq_num` - 序列号，针对用户发起的每一次写操作`Put()`或`Delete()`leveldb产生一个相应的序列号
    - `type` - 记录类型，`kTypeDeletion = 0`，表示删除记录，`kTypeValue = 1`，表示插入记录
- `user_value_size` - 用户值长度
- `user_value` - 用户值，即用户调用`DBImpl::Put(options, key, val)`传入的val

## MemTable基本参数
- `Arena arena_` - 使用arena为memtable记录分配内存
- `SkipList<const char*, Comparator> table_` - 使用跳表存储memtable记录

## MemTable::Add(seq, type, key, value) - 添加记录
- `table_.Insert(const char* memtable_record)` - 调用SkipList插入操作，O(logn)

## MemTable::Get(const LookupKey& key, std::string* value, Status* s) - 查找记录
- LookupKey数据格式
``` c++
// We construct a char array of the form:
//    klength  varint32               <-- start_
//    userkey  char[klength]          <-- kstart_
//    tag      uint64
//                                    <-- end_

const char* start_;
const char* kstart_;
const char* end_;

// LookupKey衍生出的各种key
// MemtableKey: end - start，用于在Memtable上执行查找操作
// InternalKey: end - kstart = user_key + 8(seq_num/type)，用于在leveldb内部执行查找操作
// userKey: end - 8(seq_num/type) - kstart，用于比较leveldb记录和用户键是否相等
```
- `SkipList<const char*, Comparator>::Iterator::Seek(const char* memtable_key)` - 调用SkipList查找操作，O(logn)
