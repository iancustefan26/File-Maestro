#include "usable.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>

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

