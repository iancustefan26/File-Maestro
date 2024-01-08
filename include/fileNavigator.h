#ifndef FILENAVIGATOR_H
#define  FILENAVIGATOR_H
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
struct folder
{
	std::string name, extension;
	std::string date;
	int size;
};

void drawFileBackground(sf::RenderWindow& window, bool side,bool& view_mode);

void listFile(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], int index, std::string fileName, std::string ext);

void drawFilesFromDir(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[]);

bool canOpenFolder(std::string folderPath);

std::string getFileLastModifiedTime(const std::string& filePath);

void renderSearchWindow(sf::RenderWindow& window, std::string& currentPath, bool& view_mode);

void create_files(std::string& currentPath, folder file[]);

void searchForFile(std::string &currentPath, std::string inputString, sf::RenderWindow &window,bool& view_mode);

void changhePath(std::string &currentPath, std::string &inputString, sf::RenderWindow &window);

#endif // !FILENAVIGATOR_H
