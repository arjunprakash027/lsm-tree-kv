#include "memtable.hpp"
#include "sstable.hpp"

Memtable::Memtable(const std::string& walPath) : wal_(walPath) {
}

void Memtable::put(const std::string& key, const std::string& value) {
    wal_.append(key, value, false);
    data_[key] = value;
}

std::optional<std::string> Memtable::get(const std::string& key) const {
    auto it = data_.find(key);
    if (it == data_.end()) {
        return std::nullopt;
    }
    return it->second;
}

void Memtable::flush() {
    SSTable table(data_);
    data_.clear();
}

