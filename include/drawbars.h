#ifndef DRAWBARS_H
#define DRAWBARS_H
#include <SFML/Graphics.hpp>
#include "filesize.h"

void loadToolbar(sf::RenderWindow& window, bool& view_mode);

void loadDiskSelection(sf::RenderWindow& window, int numberOfDrives, bool &view_mode, std::string &currentDisk, bool side, std::string &currentPath, static bool selected[]);

void loadBetweenLine(sf::RenderWindow& window);

void loadPathBar(sf::RenderWindow& window, bool &view_mode, bool side, sf::Event &event, std::string &currentPath);

void loadSortBar(sf::RenderWindow& window, bool& view_mode, bool side);

#endif