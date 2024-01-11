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

void renderErrorWindow(sf::RenderWindow &window,bool& view_mode) {
    sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "Error - Acces denied!");

    errorWindow.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
        sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));

    sf::Image icon;
    if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/errorwindow_icon.png")) {
        errorWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        std::cout << "Loaded window icon..." << "\n";
    }
    else {
        std::cerr << "Error when loading the window icon!" << "\n";
        return;
    }

    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                errorWindow.close();
                return;
            }
        }
        errorWindow.clear(view_mode == 0 ? sf::Color::White : sf::Color(89, 87, 87));
        renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/errorwindow_icon.png", errorWindow, sf::Vector2f(errorWindow.getSize().x / 2 - 30.f, errorWindow.getSize().y / 2 - 70.f));
        sf::Text text;
        sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

        text.setString("ACCES DENIED!");
        text.setFont(font);
        text.setCharacterSize(30);
        text.setPosition(100, 110);
        text.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
        errorWindow.draw(text);
        errorWindow.display();
    }
}

sf::Vector2i getLastClickPosition(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            return sf::Mouse::getPosition(window);
        }
    }

    return sf::Vector2i(-1, -1); // Return an invalid position if no click event occurred
}