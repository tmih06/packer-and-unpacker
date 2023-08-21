#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string readFileBytes(const std::string& filename) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile) {
        std::cerr << "Error opening the file " << filename << std::endl;
        return "";
    }

    std::ostringstream oss;
    char byte;
    while (infile.get(byte)) {
        oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(static_cast<unsigned char>(byte));
    }
    infile.close();
    return oss.str();
}

int main() {
    std::string folder_path;
    std::cout << "Path: ";
    std::getline(std::cin, folder_path);

    std::vector<std::pair<std::string, std::string>> shellcodeVector;

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            
            std::string upxcmd = "upx " + entry.path().string();
            std::system(upxcmd.c_str());

            std::string filename = entry.path().filename().string();
            std::string byteCode = readFileBytes(entry.path().string());
            std::cout << "Reading file: " << filename << " | Size: " << byteCode.size() << std::endl;

            if (!byteCode.empty()) {
                shellcodeVector.emplace_back(filename, byteCode);
            }
        }
    }

    std::ofstream outfile("shellcode.h");
    if (!outfile) {
        std::cerr << "Error opening the output file shellcode.h" << std::endl;
        return 1;
    }

    outfile << "#include <vector>\n#include <string>\n";
    outfile << "std::vector<std::pair<std::string, std::string>> shellcodeVector = {\n";
    for (const auto& entry : shellcodeVector) {
        outfile << "    {\"" << entry.first << "\", \"" << entry.second << "\"},\n";
    }
    outfile << "};\n";

    outfile.close();

    std::cout << "Shellcode written to shellcode.h successfully." << std::endl;
    
    return 0;
}
