#ifndef BUTTONS_H
#define BUTTONS_H
#include <SFML/Graphics.hpp>
#include "fileNavigator.h"
void drawCommandButtons(sf::RenderWindow& window,bool& view_mode, std::string &currentPath, folder files[],sf::Event event);
void renderF5_MOVE(sf::RenderWindow& window, std::string& currentPath, bool& view_mode, folder files[]);
void renderF6_NEW(sf::RenderWindow& window, std::string& currentPath, bool& view_mode);
void renderF4_COPY(sf::RenderWindow& window, std::string& currentPath, bool& view_mode, folder files[]);
void deleteFiles(folder files[], std::string currentPath);
void open(std::string& currentPath, folder files[], sf::RenderWindow& window, bool& view_mode);


#endif // !BUTTONS_H
