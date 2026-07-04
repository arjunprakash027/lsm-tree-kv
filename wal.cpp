#include "wal.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>

WriteAheadLog::WriteAheadLog(const std::string& path) {
    path_ = path;

    fd_ = open(path_.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd_ == -1) {
        throw std::runtime_error("failed to open");
    }
}

WriteAheadLog::~WriteAheadLog() {
    close(fd_);
}

void WriteAheadLog::append(const std::string& key, const std::string& value, bool isDelete) {
    std::string buffer;
    buffer.append(1, static_cast<char>(isDelete));

    uint32_t keylen = key.size();
    buffer.append(reinterpret_cast<const char*>(&keylen), sizeof(keylen));
    buffer.append(key);

    uint32_t valuelen = value.size();
    buffer.append(reinterpret_cast<const char*>(&valuelen), sizeof(valuelen));
    buffer.append(value);

    ssize_t written = write(fd_, buffer.data(), buffer.size());

    if (written == -1) {
        throw std::runtime_error("failed to write");
    }

    fsync(fd_);
}

