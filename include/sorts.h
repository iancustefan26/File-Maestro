#ifndef SORTS_H
#define SORTS_H
#include <filesystem>
#include "filesize.h"
#include <algorithm>
struct folder
{
	std::string info;
	folder* next;
};
void createfiles(const path& dir, int& k);
void sort_ascending(folder a[], int k);
void sort_descending(folder a[], int k);
void sort_size_ascending(folder a[], int k);
void sort_size_descending(folder a[], int k);
#endif
