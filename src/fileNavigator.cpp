#include "fileNavigator.h"
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

sf::Color bgDarkColor(89, 87, 87);
sf::Color bgLightColor(199, 199, 199);
sf::Color Grayish(160, 160, 160);
sf::Color hoverrColor(7, 148, 224, 128);
sf::Color clickeddColor(224, 20, 75);

void drawFileBackground(sf::RenderWindow& window, bool side,bool& view_mode) {
	sf::RectangleShape background(sf::Vector2f(window.getSize().x / 2, 478.f));
	sf::RectangleShape line(sf::Vector2f(window.getSize().x / 2, 2.f));
	line.setFillColor(view_mode == 0 ? Grayish : sf::Color::Black);
	line.setPosition(0.f + side * window.getSize().x / 2, 678.f);
	background.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	background.setPosition(0.f, 200.f);
	if (side == 1)
		background.setPosition(0.f + window.getSize().x / 2 + 4.f, 200.f);
	window.draw(background);
	window.draw(line);
}

void listFile(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], int index) {
	sf::RectangleShape fileBox(sf::Vector2f(window.getSize().x / 2, 30.f));
	fileBox.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	fileBox.setPosition(0.f, 200.f + index);

    sf::FloatRect iconBoxRect = fileBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	int i = index / 30;

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        fileBox.setFillColor(hoverrColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			selected[i] = !selected[i];
            fileBox.setFillColor(selected[i] == 0 ? bgDarkColor : clickeddColor);
			for (int i = 0; i < 5; ++i)
				std::cout << selected[i] << " ";
			std::cout << "\n";
        }
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
	else {
		fileBox.setFillColor(selected[i] == 0 ? bgDarkColor : clickeddColor);
	}
	window.draw(fileBox);
}

void drawFilesFromDir(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[]) {
	for (int i = 0; i < 5; ++i)
		listFile(window, side, view_mode, currentPath, selected, i * 30);
}