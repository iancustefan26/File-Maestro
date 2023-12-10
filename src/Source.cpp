#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "filesize.h"
#include "buttons.h"
#define WINDOW_W 1920
#define WINDOW_H 1080
using namespace std::filesystem;



int main() {
	//Rendering window with icon
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "File Maestro");
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
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return EXIT_SUCCESS;
			}
		}
		window.clear();
		///
		///the drawing stage
		/// 
		window.display();
	}

	return EXIT_SUCCESS;
}