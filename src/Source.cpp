#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "filesize.h"
#include "buttons.h"
#include "drawbars.h"
#define WINDOW_W 1920
#define WINDOW_H 1080
using namespace std::filesystem;

int main() {
	//Rendering window
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "File Maestro");

	///Center the window in the middle of the screen
	window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - WINDOW_W / 2,
			sf::VideoMode::getDesktopMode().height / 2 - WINDOW_H / 2));
	//Render the window icon

	sf::Image icon;
	if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/window_icon.png")) {
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		std::cout << "Loaded window icon..." << "\n";
	}
	else {
		std::cerr << "Error when loading the window icon!" << "\n";
		return EXIT_FAILURE;
	}
	///The main window loop
	bool light_dark_mode = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return EXIT_SUCCESS;
			}
		}
		window.clear(light_dark_mode == 0 ? sf::Color::White : sf::Color::Black);
		///
		///the drawing stage
		/// 
		loadToolbar(window, light_dark_mode);
		loadDiskSelection(window);
		loadBetweenLine(window);
		window.display();
	}

	return EXIT_SUCCESS;
}