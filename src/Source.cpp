#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "filesize.h"
#include "buttons.h"
#include "drawbars.h"
#include "sorts.h"
#include "fileNavigator.h"
#include "usable.h"
#include "textureCache.h"
#include "scrollbar.h"
#define WINDOW_W 1280
#define WINDOW_H 720
using namespace std::filesystem;

int numberOfDrives = getNumberOfDrives();
std::string currentDisk2 = "C:/";
std::string currentDisk = "C:/";
std::string currentPath = "C:/";
std::string currentPath2 = "C:/";
static bool selected1[] = { 1, 0, 0, 0, 0, 0, 0, 0 };
static bool selected2[] = { 1, 0, 0, 0, 0, 0, 0, 0 };


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
	bool light_dark_mode = 1;
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
		drawFileBackground(window, 0, light_dark_mode);
		drawFileBackground(window, 1, light_dark_mode);
		static bool selectedFiles1[205] = { 0 };
		static bool selectedFiles2[205] = { 0 };
		
		drawFilesFromDir(window, 0, light_dark_mode, currentPath, selectedFiles1);
		drawFilesFromDir(window, 1, light_dark_mode, currentPath2, selectedFiles2);
		loadToolbar(window, light_dark_mode);
		loadDiskSelection(window, numberOfDrives, light_dark_mode, currentDisk, 0, currentPath, selected1);
		loadDiskSelection(window, numberOfDrives, light_dark_mode, currentDisk2, 1, currentPath2, selected2);
		loadPathBar(window, light_dark_mode, 0, event, currentPath);
		loadPathBar(window, light_dark_mode, 1, event, currentPath2);
		loadBetweenLine(window, light_dark_mode);
		drawCommandButtons(window,light_dark_mode);
		loadSortBar(window, light_dark_mode, 0);
		loadSortBar(window, light_dark_mode, 1);
		renderScroll(window,event );
		window.display();
	}


	return EXIT_SUCCESS;
}

