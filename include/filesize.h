#ifndef FILESIZE_H
#define FILESIZE_H
#include <iostream>
#include <filesystem>

using namespace std::filesystem;

std::uintmax_t getDirectorySize(const path& dir);

void listFilesFromDir(const path& dir);

void createDirInPath(path& myPath, const std::string fileName);

#endif // !FILESIZE_H

