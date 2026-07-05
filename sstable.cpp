#include <filesystem>
#include <string>
#include "sstable.hpp"
#include <string_view>
#include <charconv>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

std::string SSTable::nextPath() {
    int maxN = -1;
    for (const auto& entry : std::filesystem::directory_iterator("data")) {
        std::string filename = entry.path().filename().string();
        std::string_view name(filename);

        if (name.starts_with("sstable_") && name.ends_with(".db")) {
            name.remove_prefix(8);
            name.remove_suffix(3);

            int fileNumber = 0;
            auto [ptr, ec] = std::from_chars(name.data(), name.data() + name.size(), fileNumber);

            if (ec == std::errc()) {
                if (fileNumber > maxN){
                    maxN = fileNumber;
                }
            }
        }
    }

    return "data/sstable_" + std::to_string(maxN + 1) + ".db";
}

SSTable::SSTable(const std::map<std::string, std::string>& data) {
    std::string path_ = SSTable::nextPath();
    auto fd = open(path_.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        throw std::runtime_error("failed to open sstable");
    }

    for (const auto& [key, value] : data) {
        std::string buffer;
        uint32_t keylen = key.size();
        uint32_t valuelen = value.size();

        buffer.append(reinterpret_cast<const char*>(&keylen), sizeof(keylen));
        buffer.append(key);

        buffer.append(reinterpret_cast<const char*>(&valuelen), sizeof(valuelen));
        buffer.append(value);

        ssize_t written = write(fd, buffer.data(), buffer.size());

        if (written == -1) {
            throw std::runtime_error("failed to write");
        }   
    }

    fsync(fd);
    close(fd);
}