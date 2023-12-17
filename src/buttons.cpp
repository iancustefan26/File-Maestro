#include <SFML/Graphics.hpp>
#include "buttons.h"
#include <vector>
#include <filesystem>
#include <iostream>

using namespace std::filesystem;


void makeButton(sf::RenderWindow& window, std::string name, float index) {
    sf::Color defaultColor(51, 53, 54);
    sf::Color hoverColor(7, 148, 224, 128);
    sf::Color clickedColor(224, 20, 75);

    sf::RectangleShape iconBox(sf::Vector2f(213.f, 40.f));
    iconBox.setPosition(0.f + index, 680.f);
    iconBox.setFillColor(defaultColor);

    sf::RectangleShape line(sf::Vector2f(1.f, 40.f));
    line.setFillColor(sf::Color::Black);
    line.setPosition(iconBox.getPosition().x + 213.f, 680.f);

    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        iconBox.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            iconBox.setFillColor(clickedColor);
        }
    }
    else {
        iconBox.setFillColor(defaultColor);
    }
    window.draw(iconBox);
    window.draw(line);
}

void drawCommandButtons(sf::RenderWindow& window) {
	std::vector<std::string> buttonNames;
	buttonNames.push_back("F3 Open");
	buttonNames.push_back("F4 Copy");
	buttonNames.push_back("F5 Move");
	buttonNames.push_back("F6 New Folder");
	buttonNames.push_back("F7 Delete");
	buttonNames.push_back("Alt+F4 Exit");
	for (float i = 0; i < 6; ++i)
		makeButton(window, buttonNames[i], 214.f * i);
}