#include "sorts.h"
#include <filesystem>
#include "filesize.h"
#include <algorithm>
#include <chrono>

bool sort_za(folder a, folder b)
{
	return a.name > b.name;
}
bool sort_az(folder a, folder b)
{
	return a.name < b.name;
}
void sort_ascending(folder a[], int k)
{
	std::sort(a, a + k, sort_az);
}
void sort_descending(folder a[], int k)
{
	std::sort(a, a + k, sort_za);
}
bool sort_sascending(folder a, folder b)
{
	return a.size < b.size;
}
bool sort_sdescending(folder a, folder b)
{
	return a.size > b.size;
}
bool sort_date_ascending(folder a, folder b)
{
	return last_write_time(a.path_file) < last_write_time(b.path_file);
}
bool sort_date_descending(folder a, folder b)
{
	return last_write_time(a.path_file) > last_write_time(b.path_file);
}
void sort_size_ascending(folder a[], int k)
{
	std::sort(a, a + k, sort_sascending);
}
void sort_size_descending(folder a[], int k)
{
	std::sort(a, a + k, sort_sdescending);
}
void sort_date_asc(folder a[], int k)
{
	std::sort(a, a + k, sort_date_ascending);
}
void sort_date_des(folder a[], int k)
{
	std::sort(a, a + k, sort_date_descending);
}
bool sort_extension_asc(folder a, folder b)
{
	return a.extension < b.extension;
}
bool sort_extension_des(folder a, folder b)
{
	return a.extension > b.extension;
}
void sort_ext_asc(folder a[], int k)
{
	std::sort(a, a + k, sort_extension_asc);
}
void sort_ext_des(folder a[], int k)
{
	std::sort(a, a + k, sort_extension_des);
}
void choose_sort(int type, int index,folder a[],int numFiles)
{
	if (index == 0) {
		if (type == 0) return;
		if (type == 1) sort_ascending(a, numFiles);
		if (type == 2) sort_descending(a, numFiles);
	}
	if (index == 1) {
		if (type == 0) return;
		if (type == 1) sort_ext_asc(a, numFiles);
		if (type == 2) sort_ext_des(a, numFiles);
	}
	if (index == 2) {
		if (type == 0) return;
		if (type == 1) sort_date_asc(a, numFiles);
		if (type == 2) sort_date_des(a, numFiles);
	}
	if (index == 3) {
		if (type == 0) return;
		if (type == 1) sort_size_ascending(a, numFiles);
		if (type == 2) sort_size_descending(a, numFiles);
	}
}