#include <iostream>
#include "memtable.hpp"

int main() {
    Memtable mt("data.wal");
    mt.put("hello", "world");
    mt.put("c", "pp");

    auto val = mt.get("c");

    if (val) {
        std::cout << *val << "\n";
    } else {
        std::cout << "not found key\n";
    }
}

