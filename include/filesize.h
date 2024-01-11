#ifndef FILESIZE_H
#define FILESIZE_H
#include <iostream>
#include <filesystem>

using namespace std::filesystem;

std::uintmax_t getDirectorySize(const path& dir);

int getNumberOfFilesFromDir(std::string dir);

void listFilesFromDir(const path& dir);

void createDirInPath(std::string& myPath, const std::string fileName);

int getNumberOfDrives();

std::string getSizeOfDrive(std::string path);

std::string compressSize(uintmax_t sizeToCompress);

#endif // !FILESIZE_H

