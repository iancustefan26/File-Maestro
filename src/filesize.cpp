#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "filesize.h"

using namespace std::filesystem;

std::uintmax_t getDirectorySize(const path& dir) {
    std::uintmax_t size = 0;
    for (const auto& entry : recursive_directory_iterator(dir))
        if (is_regular_file(entry)) {
            size += file_size(entry);
        }

    return size;
}

void listFilesFromDir(const path& dir) {
    std::cout << "Files in directory: " << std::endl;
    for (const auto& entry : directory_iterator(dir)) {
        std::cout << entry.path().filename() << "\n";
    }
}

void createDirInPath(std::string& myPath, const std::string fileName) {
        if (exists(myPath)) {
            std::cout << "Directory exists: " << myPath << std::endl;
            try {
                path new_path = myPath + "/" + fileName;
                create_directory(new_path);
                std::cout << "New directory named " << fileName << " has been created in " << myPath << std::endl;
            }
            catch (filesystem_error& ex) {
                std::cerr << "Error creating the new file: " << ex.what() << std::endl;
                return;
            }
        }
        else
            std::cout << "Directory doensn't exist!";
}


int getNumberOfDrives() {
    
    int count = 0;
    for (char driveLetter = 'C'; driveLetter <= 'Z'; ++driveLetter){
        std::string rootPath = std::string(1, driveLetter) + ":\\";
        try {
            if (exists(rootPath)) {
                count++;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    return count;
}

std::string uint2str(uintmax_t a) {
    if (a == -1) {
        return "<DIR>";
    }
    else if (a == 0) {
        return "0";
    }

    std::string stringNumber;

    while (a) {
        stringNumber.insert(stringNumber.begin(), char(a % 10 + '0'));
        a /= 10;
    }

    return stringNumber;
}

std::string compressSize(uintmax_t sizeToCompress) {
    std::string dim = " KMGT";
    double doubleSize = sizeToCompress;
    unsigned long long intSize = 0;
    int dimIterator = 0;

    while (doubleSize > 999) {
        doubleSize /= 1024;
        intSize = (unsigned long long)(doubleSize * 10);
        dimIterator++;
    }

    std::string driveSize = uint2str(intSize / 10);
    std::string dimLetter = "";

    if (dim[dimIterator] != ' ') {
        dimLetter = dim[dimIterator];
    }
    return driveSize + "." + uint2str(intSize % 10) + " " + dimLetter + "B";
}

std::string getSizeOfDrive(std::string path) {
    space_info size = space(path);
    return compressSize(size.free) + " free of " + compressSize(size.capacity);
}

int getNumberOfFilesFromDir(std::string dir) {
    int number = 0;
    for (const auto& entry : directory_iterator(dir))
        number++;
    return number;
}