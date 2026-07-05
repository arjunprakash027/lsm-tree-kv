# lsm-tree-kv

A minimal LSM-tree (Log-Structured Merge-tree) key-value store, written from scratch in C++ as a learning project.

## What's implemented so far

- **Write-Ahead Log (WAL)**: every write is appended to an on-disk log before being applied in memory, for durability.
- **Memtable**: an in-memory sorted key-value store backed by `std::map`, used as the write buffer.
- **SSTable flush**: when triggered, the memtable's sorted contents are flushed to an immutable, sorted on-disk file (an "SSTable").

## Planned next

- Memory-mapped reads from SSTables
- Compaction of multiple SSTables
- Bloom filters for faster negative lookups

## Building and running

```bash
./run.sh
```
