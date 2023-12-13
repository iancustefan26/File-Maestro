#include "sorts.h"
#include <filesystem>
#include "filesize.h"
#include <algorithm>
void createfiles(const path& dir, int& k) {
	folder files[100];
	for (const auto& entry : directory_iterator(dir)) {
		files[k++].info = entry.path().filename().string();

	}
}
bool sort_za(folder a, folder b)
{
	return a.info > b.info;
}
bool sort_az(folder a, folder b)
{
	return a.info < b.info;
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
	return getDirectorySize(a.info) < getDirectorySize(b.info);
}
bool sort_sdescending(folder a, folder b)
{
	return getDirectorySize(a.info) > getDirectorySize(b.info);
}
void sort_size_ascending(folder a[], int k)
{
	std::sort(a, a + k, sort_sascending);
}
void sort_size_descending(folder a[], int k)
{
	std::sort(a, a + k, sort_sdescending);
}