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

void createDirInPath(path& myPath, const std::string fileName) {
        if (exists(myPath)) {
            std::cout << "Directory exists: " << myPath << std::endl;
            try {
                path new_path = myPath / fileName;
                create_directory(new_path);
                std::cout << "New directory named " << fileName << " has been created in " << myPath << std::endl;
            }
            catch (filesystem_error& ex) {
                std::cerr << "Error chrating the new file: " << ex.what() << std::endl;
                return;
            }
        }
        else
            std::cout << "Directory doensn't exist!";
}


int getNumberOfDrives() {
    int count = 0;
    for (char driveLetter = 'A'; driveLetter <= 'Z'; ++driveLetter){
        std::string rootPath = std::string(1, driveLetter) + ":\\";
        if (exists(rootPath)) {
            count++;
        }
    }

    return count;
}