#ifndef DRAWBARS_H
#define DRAWBARS_H
#include <SFML/Graphics.hpp>
#include "filesize.h"

void loadToolbar(sf::RenderWindow& window, bool& view_mode);

void loadDiskSelection(sf::RenderWindow& window, int numberOfDrives, bool &view_mode);

void loadBetweenLine(sf::RenderWindow& window);

#endif