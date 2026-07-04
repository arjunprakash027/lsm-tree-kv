#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct Entry {
    std::string key;
    std::string value;
    bool isDelete;
};

class WriteAheadLog {
public:
    explicit WriteAheadLog(const std::string& path);
    ~WriteAheadLog();

    void append(const std::string& key, const std::string& value, bool isDelete);
    std::vector<Entry> replay();

private:
    int fd_;
    std::string path_;
};

