#pragma once
#include <string>
#include <map>

class SSTable {
public: 
    explicit SSTable(const std::map<std::string, std::string>& data);
private:
    static std::string nextPath();
};