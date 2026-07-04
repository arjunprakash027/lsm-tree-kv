#pragma once
#include <string>
#include <map>
#include <optional>
#include "wal.hpp"

class Memtable {
public:
    explicit Memtable(const std::string& walPath);

    void put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;

private:
    std::map<std::string, std::string> data_;
    WriteAheadLog wal_;
};