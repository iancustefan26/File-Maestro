#ifndef FILENAVIGATOR_H
#define  FILENAVIGATOR_H
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <chrono>
struct folder
{
	std::string name, extension,path_file;
	std::time_t date;
	std::uintmax_t size;

};
void drawFileBackground(sf::RenderWindow& window, bool side,bool& view_mode);

void listFile(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], int index, std::string fileName, std::string ext, sf::Event& event, bool& scrolled, float& offsetY, folder files[]);

void drawFilesFromDir(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], sf::Event& event, bool& scrolled, float& offsetY, int sort_buttons0[], int sort_buttons1[]);

bool canOpenFolder(std::string folderPath);

std::string getFileLastModifiedTime(const std::string& filePath);

void create_files(std::string& currentPath, folder files[]);

std::string replaceBackslashes(const std::string& inputString);

void renderSearchWindow(sf::RenderWindow& window, std::string& currentPath, bool& view_mode);

void searchForFile(std::string &currentPath, std::string inputString, sf::RenderWindow &window,bool& view_mode);

void changePath(std::string &currentPath, std::string &inputString, sf::RenderWindow &window, bool &view_mode);

#endif // !FILENAVIGATOR_H
