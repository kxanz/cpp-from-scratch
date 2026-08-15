# Hash Table
 
A simple hash table implementation in C++ using separate chaining for collision handling.
 
## How It Works
 
The table is a fixed array of buckets. Each bucket is a `std::list` of key–value pairs (`int` → `string`). A hash function maps each key to a bucket index; when two keys land in the same bucket, they're stored side by side in that bucket's list (separate chaining).
 
## Operations
 
| Method | Description |
|---|---|
| `insertItem(key, value)` | Insert a key–value pair, or replace the value if the key already exists |
| `removeItem(key)` | Remove the entry for a key |
| `searchTable(key)` | Look up the value for a key |
| `isEmpty()` | Return whether the table holds any entries |
| `printTable()` | Print all stored key–value pairs |
 
## Build & Run
 
```bash
g++ hash_table.cpp -o hash_table
./hash_table
```
 
## Notes
 
Educational implementation for practicing hashing, collision handling with separate chaining, and working with `std::list`.
 
