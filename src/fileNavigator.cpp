#include "fileNavigator.h"
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Color bgColor(89, 87, 87);

void drawFileBackground(sf::RenderWindow& window, bool side) {
	sf::RectangleShape background(sf::Vector2f(window.getSize().x / 2, 478.f));
	sf::RectangleShape line(sf::Vector2f(window.getSize().x / 2, 2.f));
	line.setFillColor(sf::Color::Black);
	line.setPosition(0.f + side * window.getSize().x / 2, 678.f);
	background.setFillColor(bgColor);
	background.setPosition(0.f, 200.f);
	if (side == 1)
		background.setPosition(0.f + window.getSize().x / 2 + 4.f, 200.f);
	window.draw(background);
	window.draw(line);
}