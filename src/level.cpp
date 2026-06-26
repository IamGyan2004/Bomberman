#include "level.h"
#include <fstream>
#include <iostream>

bool loadLevelFile(const std::string& path, std::vector<std::string>& outLevel) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Failed to open level file: " << path << "\n";
        return false;
    }

    outLevel.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        outLevel.push_back(line);
    }
    return true;
}
