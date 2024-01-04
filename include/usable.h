#ifndef USABLE_H
#define USABLE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <map>
#include "textureCache.h"

bool isDoubleClick( sf::RenderWindow& window);

sf::Texture& getTexture(const std::string& filePath);

void renderIcon(const std::string& iconPath, sf::RenderWindow& window, sf::Vector2f position);

sf::Font& getFont(const std::string& fontPath);

void renderErrorWindow(sf::RenderWindow &window);

#endif
