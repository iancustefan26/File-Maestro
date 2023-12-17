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

    sf::Text buttonText;
    sf::Font font;
    if (!font.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf")) {
        std::cerr << "Couldn't load the font quicksand for diskspace";
        return;
    }
    buttonText.setFillColor(sf::Color::White);
    buttonText.setFont(font);
    buttonText.setCharacterSize(24);
    buttonText.setString(name);
    //buttonText.setPosition(iconBox.getPosition().x + 45.f, iconBox.getPosition().y + 4.f);
    sf::Vector2f boxPosition(iconBox.getPosition().x, iconBox.getPosition().y);
    sf::Vector2f boxSize(iconBox.getSize().x, iconBox.getSize().y);
    sf::Vector2f textPosition;
    textPosition.x = boxPosition.x + (boxSize.x - buttonText.getGlobalBounds().width) / 2;
    textPosition.y = boxPosition.y + (boxSize.y - buttonText.getGlobalBounds().height) / 2 - 5.f;
    buttonText.setPosition(textPosition);
    window.draw(iconBox);
    window.draw(buttonText);
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