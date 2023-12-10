#include <SFML/Graphics.hpp>
#include <filesystem>
#include <drawbars.h>
#include <iostream>
#define WINDOW_W 1920
#define WINDOW_H 1080
using namespace std::filesystem;

void renderIcon(const std::string iconPath, sf::RenderWindow& window) {
    sf::RectangleShape iconBox(sf::Vector2f(60.f, 60.f));
    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();

    sf::Image icon;
    if (icon.loadFromFile(iconPath)) {
        sf::Texture iconTexture;
        iconTexture.loadFromImage(icon);
        sf::Sprite iconSprite(iconTexture);
        iconSprite.setPosition(8.f, 10.f);
        window.draw(iconSprite);
        std::cout << "Loaded window icon..." << "\n";
    }
    else {
        std::cerr << "Error when loading the window icon!" << "\n";
        return;
    }
}

void drawToolbar(sf::RenderWindow& window) {
	sf::Color defaultColor(51, 53, 54);
    sf::Color hoverColor(7, 148, 224, 128);
    sf::Color clickedColor(224, 20, 75);

    sf::RectangleShape toolbar(sf::Vector2f(window.getSize().x, 70.f));
    sf::RectangleShape iconBox(sf::Vector2f(70.f, 70.f));

    toolbar.setPosition(0.f, 0.f);
    toolbar.setFillColor(defaultColor);
    iconBox.setPosition(0.f, 0.f);
    iconBox.setFillColor(defaultColor);


    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Image icon;

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        iconBox.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            iconBox.setFillColor(clickedColor);
    }
    else {
        iconBox.setFillColor(defaultColor);
    }
    window.draw(toolbar);
    window.draw(iconBox);
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/refresh_icon.png", window);
}