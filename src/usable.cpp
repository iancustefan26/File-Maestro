#include "usable.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <map>
#include "textureCache.h"

std::map<std::string, sf::Texture> textureCache;
std::map<std::string, sf::Font> fontCache;
bool loaded = false;

bool isDoubleClick(sf::RenderWindow& window) {
    static sf::Clock clock;
    static sf::Vector2i lastClickPosition;
    static bool firstClick = true;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i clickPosition = sf::Mouse::getPosition(window);

        if (!firstClick && clock.getElapsedTime().asMilliseconds() < 500
            && std::abs(clickPosition.x - lastClickPosition.x) < 5
            && std::abs(clickPosition.y - lastClickPosition.y) < 5) {
            // Double-click detected
            clock.restart();
            firstClick = true;
            return true;
        }

        firstClick = false;
        lastClickPosition = clickPosition;
        clock.restart();
    }
    else {
        firstClick = true; // Reset on mouse release to allow next click
    }

    return false;
}


sf::Texture& getTexture(const std::string& filePath) {
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        //std::cout << "Already cached textures, loaded...";
        // Texture is in the cache, return the cached texture
        return it->second;
    }
    else {
        // Texture is not in the cache, load it from file
        sf::Texture texture;
        if (texture.loadFromFile(filePath)) {
            std::cout << "Texture not in cache, loading...\n";
            // Successfully loaded, store in the cache
            textureCache[filePath] = texture;
            return textureCache[filePath];
        }
        else {
            texture.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/unknown_icon.png");
            std::cout << "Error loading textures, loaded the default one\n";
            textureCache[filePath] = texture;
            return textureCache[filePath];
        }
    }
}


void renderIcon(const std::string& iconPath, sf::RenderWindow& window, sf::Vector2f position) {
    sf::RectangleShape iconBox(sf::Vector2f(60.f, 60.f));
    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();

    // Load or retrieve texture from cache
    sf::Texture& iconTexture = getTexture(iconPath);

    sf::Sprite iconSprite(iconTexture);
    iconSprite.setPosition(position);

    window.draw(iconSprite);
}

sf::Font& getFont(const std::string& fontPath) {
    auto it = fontCache.find(fontPath);
    if (it != fontCache.end()) {
        // Font is in the cache, return the cached font
        return it->second;
    }
    else {
        // Font is not in the cache, load it from file
        sf::Font font;
        if (font.loadFromFile(fontPath)) {
            // Successfully loaded, store in the cache
            fontCache[fontPath] = font;
            return fontCache[fontPath];
        }
        else {
            // Handle loading failure (you may want to use a default font)
            std::cerr << "Couldn't load the font " << fontPath << "\n";
            // Return a default font or throw an exception
            throw std::runtime_error("Failed to load font");
        }
    }
}