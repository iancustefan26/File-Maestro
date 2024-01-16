#ifndef SORTS_H
#define SORTS_H
#include <filesystem>
#include "filesize.h"
#include <algorithm>
#include "fileNavigator.h"
#include <chrono>
void sort_ascending(folder a[], int k, int start);
void sort_descending(folder a[], int k, int start);
void sort_size_ascending(folder a[], int k, int start);
void sort_size_descending(folder a[], int k, int start);
void sort_date_asc(folder a[], int k, int start);
void sort_date_des(folder a[], int k, int start);
void sort_ext_des(folder a[], int k,int start);
void sort_ext_asc(folder a[], int k,int start);
void choose_sort(int type, int index, folder a[], int numFiles, int start);
#endif
