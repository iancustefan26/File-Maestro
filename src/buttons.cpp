#include "buttons.h"
#include <SFML/Graphics.hpp>

void createButton(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, std::string name, sf::Font& font) {
    sf::RectangleShape button(size);
    sf::Color colorButt(196, 195, 192);
    button.setPosition(position);
    button.setFillColor(sf::Color::Green);

    sf::Text buttonText;
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString(name);
    buttonText.setFont(font);
    buttonText.setCharacterSize((size.x / 10 + size.y / 10) / 2);

    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(position.x + (size.x - textBounds.width) / 2, position.y + (size.y - textBounds.height) / 2);

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool buttonClicked = false;

    if (button.getGlobalBounds().contains(mousePos)) {
        button.setFillColor(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? colorButt : sf::Color::Red);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            buttonClicked = true;
    }
    else
        button.setFillColor(sf::Color::Green);


    window.draw(button);
    window.draw(buttonText);
}
