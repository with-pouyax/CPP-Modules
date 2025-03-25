#include <iostream>
#include <fstream>
#include <string>

void replaceInFile(const std::string& filename, const std::string& s1, const std::string& s2) {
    std::fstream inputFile; 
    inputFile.open(filename.c_str(), std::ios::in); //open the file in read mode
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file: " << filename << std::endl;
        return;
    }

    std::fstream outputFile;
    outputFile.open((filename + ".replace").c_str(), std::ios::out);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create output file: " << filename << ".replace" << std::endl;
        inputFile.close();
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        size_t pos = 0;
        while ((pos = line.find(s1, pos)) != std::string::npos) {
            line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
            pos += s2.length();
        }
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    if (s1.empty()) {
        std::cerr << "Error: s1 cannot be empty" << std::endl;
        return 1;
    }

    replaceInFile(filename, s1, s2);
    return 0;
} 