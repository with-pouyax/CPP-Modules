#include <iostream>
#include <fstream>
#include <string>

void replaceInFile(const std::string& filename, const std::string& s1, const std::string& s2) {
    // we make a ifstream object, it is like openning a file in read mode
    std::ifstream inputFile(filename.c_str());
    // good() checks if:
    // - file exists
    // - file is open
    // - file has read permissions
    // - no errors have occurred
    if (!inputFile.good()) {
        std::cerr << "Error: Cannot access file: " << filename << std::endl;
        return;
    }

    // we check if input file is empty
    // seekg() method is used to move the file pointer to a specific position
    // first argument is offset, means the number of bytes to move the pointer from the second argument
    // second argument is direction, means the direction to move the pointer
    // for direction we have std::ios::end, std::ios::beg, std::ios::cur
    // end means move the pointer to the end of the file
    // beg means move the pointer to the beginning of the file
    // cur means move the pointer from the current position

    inputFile.seekg(0, std::ios::end);
    // tellg() method returns the current position of the file pointer
    // if the file is empty, the position will be 0
    bool isEmpty = false;
    if (inputFile.tellg() == 0) {
        std::cerr << "Warning: File is empty: " << filename << std::endl;
        isEmpty = true;
    }
    //reset the file pointer to the beginning of the file
    inputFile.seekg(0, std::ios::beg);

    // we make a ofstream object, it is creating a new file and openning it in write mode
    std::ofstream outputFile((filename + ".replace").c_str());
    // is_open() checks if:
    // - file is open
    // - file has write permissions
    // - no errors have occurred
    
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create output file: " << filename << ".replace" << std::endl;
        inputFile.close();
        return;
    }

    if (isEmpty) {
        outputFile.close();
        inputFile.close();
    }

    std::string line;
    // we read the file line by line
    while (std::getline(inputFile, line)) {
        // Only try to replace if s1 is not empty
        if (!s1.empty()) {
            size_t pos = 0;
            // find() has 2 arguments:
            // first argument is the string to find
            // second argument is the position to start searching from
            // if the string is not found, find() returns std::string::npos
            while ((pos = line.find(s1, pos)) != std::string::npos) { 
                // substr() can take 1 or 2 arguments:
                // for example: line.substr(0, 5) will return the first 5 characters of the string
                // for example: line.substr(5) will return the string from the 5th character to the end
                line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
                // we move the position to the end of the string we just replaced for the next iteration
            }
        }
        outputFile << line; // write the line to the output file
        // if the end of the file is not reached, write a newline to the output file
        if (!inputFile.eof()) {
            outputFile << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();
}

// filename is the file to read
// s1 is the string to replace
// s2 is the string to replace with
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    replaceInFile(filename, s1, s2);
    return 0;
}