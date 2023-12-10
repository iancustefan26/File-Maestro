#include <SFML/Graphics.hpp>
#include <filesystem>
#include <drawbars.h>
#include <iostream>
#define WINDOW_W 1920
#define WINDOW_H 1080
using namespace std::filesystem;

bool loaded = false;

void renderIcon(const std::string iconPath, sf::RenderWindow& window, sf::Vector2f position) {
    sf::RectangleShape iconBox(sf::Vector2f(60.f, 60.f));
    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();

    sf::Image icon;
    if (icon.loadFromFile(iconPath)) {
        sf::Texture iconTexture;
        iconTexture.loadFromImage(icon);
        sf::Sprite iconSprite(iconTexture);
        iconSprite.setPosition(position); ///inital 8.f, 10.f -> 70.f mai in dreapta(x)
        window.draw(iconSprite);
        if (!loaded) std::cout << "Loaded toolbar icon..." << "\n", loaded = true;
    }
    else {
        if(!loaded) std::cerr << "Error when loading the toolbar icon!" << "\n", loaded = true;
        return;
    }
}

void drawIconBoxes(sf::RenderWindow& window, const float index) {
    sf::Color defaultColor(51, 53, 54);
    sf::Color hoverColor(7, 148, 224, 128);
    sf::Color clickedColor(224, 20, 75);

    sf::RectangleShape iconBox(sf::Vector2f(70.f, 70.f));
    iconBox.setPosition(0.f + index, 0.f);
    iconBox.setFillColor(defaultColor);

    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        iconBox.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            iconBox.setFillColor(clickedColor);
    }
    else {
        iconBox.setFillColor(defaultColor);
    }
    window.draw(iconBox);
}

void drawToolbar(sf::RenderWindow& window) {
	sf::Color defaultColor(51, 53, 54);
  
    sf::RectangleShape toolbar(sf::Vector2f(window.getSize().x, 70.f));
    toolbar.setPosition(0.f, 0.f);
    toolbar.setFillColor(defaultColor);

    window.draw(toolbar);
    for (int i = 0; i < 4; ++i)
        drawIconBoxes(window, i * 70);
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/refresh_icon.png", window, sf::Vector2f(8.f, 10.f));
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/terminal_icon.png", window, sf::Vector2f(78.f, 10.f));
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/notepad_icon.png", window, sf::Vector2f(152.f, 10.f));
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/dark_light_mode_icon.png", window, sf::Vector2f(222.f, 10.f));
}