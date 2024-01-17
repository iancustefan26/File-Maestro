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
int sort_buttons0[4] = {0}; // 0 for default 1 for ascending -1 for descending
int sort_buttons1[4] = {0}; // 0 for default 1 for ascending -1 for descending
bool scrolled = false;
float offsetY1 = 200.f;
float offsetY2 = 200.f;
bool lastClickedSide = 0;
bool sorted = false;
folder files1[1000];
folder files2[1000];
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
	static bool Selected[250], Selected1[250];
	///The main window loop
	bool light_dark_mode = 1;
	//create_files(currentPath, files);
	//for (int i = 0; i <= 50; i++) std::cout << files[i].name << "\n";
	while (window.isOpen()) {
		sf::Event event;
		sf::Vector2i clickPosition = getLastClickPosition(window);
		
		if (clickPosition != sf::Vector2i(-1, -1))
			if (clickPosition.y >= 200 && clickPosition.y <= 680)
				if (clickPosition.x > window.getSize().x / 2)
					lastClickedSide = 1;
				else lastClickedSide = 0;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return EXIT_SUCCESS;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F4 && event.key.alt) {
					window.close();
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F5 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					if(lastClickedSide==0)renderF5_MOVE(window, currentPath, light_dark_mode, files1, Selected);
					else renderF5_MOVE(window, currentPath2, light_dark_mode, files2, Selected1);
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F3 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					if(lastClickedSide==0 )open(currentPath, files1, window, light_dark_mode, Selected);
					else open(currentPath2, files2, window, light_dark_mode, Selected1);
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F6 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					if (lastClickedSide == 0) renderF6_NEW(window, currentPath, light_dark_mode);
					else renderF6_NEW(window, currentPath2, light_dark_mode);
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F7 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					if(lastClickedSide==0) deleteFiles(files1, currentPath, Selected);
					else deleteFiles(files2, currentPath2, Selected1);
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F4 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
					if(lastClickedSide==0) renderF4_COPY(window, currentPath, light_dark_mode, files1, Selected);
					else renderF4_COPY(window, currentPath2, light_dark_mode, files2, Selected1);
				}
			}
			
		}
		
		window.clear(light_dark_mode == 0 ? sf::Color::White : sf::Color::Black);
		///
		///the drawing stage
		/// 
		drawFileBackground(window, 0, light_dark_mode);
		drawFileBackground(window, 1, light_dark_mode);
		
		drawFilesFromDir(window, 0, light_dark_mode, currentPath, event, scrolled, offsetY1, sort_buttons0, sort_buttons1,files1,files2,Selected);
		drawFilesFromDir(window, 1, light_dark_mode, currentPath2, event, scrolled, offsetY2, sort_buttons0, sort_buttons1,files1,files2,Selected1);
		loadToolbar(window, light_dark_mode);
		loadDiskSelection(window, numberOfDrives, light_dark_mode, currentDisk, 0, currentPath, selected1, offsetY1, offsetY2);
		loadDiskSelection(window, numberOfDrives, light_dark_mode, currentDisk2, 1, currentPath2, selected2, offsetY1, offsetY2);
		loadPathBar(window, light_dark_mode, 0, event, currentPath);
		loadPathBar(window, light_dark_mode, 1, event, currentPath2);
		loadBetweenLine(window, light_dark_mode);
		lastClickedSide == 0 ? drawCommandButtons(window, light_dark_mode, currentPath, files1,event,Selected) : drawCommandButtons(window, light_dark_mode, currentPath2, files2,event,Selected1);
		loadSortBar(window, light_dark_mode, 0, sort_buttons0, sort_buttons1, files1,Selected);
		loadSortBar(window, light_dark_mode, 1, sort_buttons0, sort_buttons1, files2,Selected1);
		
		window.display();
		
	}
	

	return EXIT_SUCCESS;
}

