#ifndef BUTTONS_H
#define BUTTONS_H
#include <SFML/Graphics.hpp>
#include "fileNavigator.h"
void drawCommandButtons(sf::RenderWindow& window,bool& view_mode, std::string &currentPath, folder files[],sf::Event event,static bool Slected[]);
void renderF5_MOVE(sf::RenderWindow& window, std::string& currentPath, bool& view_mode, folder files[],static bool Selected[]);
void renderF6_NEW(sf::RenderWindow& window, std::string& currentPath, bool& view_mode);
void renderF4_COPY(sf::RenderWindow& window, std::string& currentPath, bool& view_mode, folder files[],static bool Selected[]);
void deleteFiles(folder files[], std::string currentPath,static bool Selected[]);
void open(std::string& currentPath, folder files[], sf::RenderWindow& window, bool& view_mode,static bool Selected[]);


#endif // !BUTTONS_H
