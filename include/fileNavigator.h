#ifndef FILENAVIGATOR_H
#define  FILENAVIGATOR_H
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

void drawFileBackground(sf::RenderWindow& window, bool side,bool& view_mode);

void listFile(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], int index, std::string fileName, std::string ext);

void drawFilesFromDir(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[]);

#endif // !FILENAVIGATOR_H
