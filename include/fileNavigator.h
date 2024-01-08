#ifndef FILENAVIGATOR_H
#define  FILENAVIGATOR_H
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

void drawFileBackground(sf::RenderWindow& window, bool side,bool& view_mode);

void listFile(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], int index, std::string fileName, std::string ext, sf::Event& event, bool& scrolled, float& offsetY);

void drawFilesFromDir(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], sf::Event& event, bool& scrolled, float& offsetY);

bool canOpenFolder(std::string folderPath);

std::string getFileLastModifiedTime(const std::string& filePath);

void renderSearchWindow(sf::RenderWindow& window, std::string& currentPath, bool& view_mode);

void searchForFile(std::string &currentPath, std::string inputString, sf::RenderWindow &window,bool& view_mode);

void changePath(std::string &currentPath, std::string &inputString, sf::RenderWindow &window, bool &view_mode);

#endif // !FILENAVIGATOR_H
