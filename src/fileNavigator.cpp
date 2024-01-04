#include "fileNavigator.h"
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "filesize.h"
#include "drawbars.h"
#include "usable.h"
#include "textureCache.h"


sf::Color bgDarkColor(89, 87, 87);
sf::Color bgLightColor(199, 199, 199);
sf::Color Grayish(160, 160, 160);
sf::Color hoverrColor(7, 148, 224, 128);
sf::Color clickeddColor(224, 20, 75);

void clearSelected(static bool selected[]) {
	for (int i = 0; i < 205; ++i)
		selected[i] = 0;
}

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

void drawBackFatherPath(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[]) {
	sf::RectangleShape fileBox(sf::Vector2f(window.getSize().x / 2, 30.f));
	fileBox.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	fileBox.setPosition(0.f + window.getSize().x / 2 * side, 200.f);

	sf::FloatRect iconBoxRect = fileBox.getGlobalBounds();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	int i = 0;

	if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && fileBox.getPosition().y >= 200.f && fileBox.getPosition().y <= 660.f) {
		fileBox.setFillColor(selected[i] == 0 ? hoverrColor : clickeddColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (isDoubleClick(window)) {
				std::cout << "Double click!\n";
				size_t lastSlashPos = currentPath.find_last_of('/');
				currentPath = currentPath.substr(0, lastSlashPos);
				clearSelected(selected);
			}
			selected[i] = !selected[i];
			fileBox.setFillColor(selected[i] == 0 ? bgDarkColor : clickeddColor);
			/*
			for (int i = 0; i < 5; ++i)
				std::cout << selected[i] << " ";
			std::cout << "\n";
			*/
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	else {
		fileBox.setFillColor(selected[i] == 0 ? bgDarkColor : clickeddColor);
	}
	window.draw(fileBox);

	renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/back_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));

	sf::Font font;
	sf::Text text;
	if (!font.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf")) {
		std::cerr << "Couldn't load the font quicksand for diskspace";
		return;
	}

	text.setFont(font);
	text.setCharacterSize(15);
	text.setString("[...]");
	text.setPosition(fileBox.getPosition().x + 40.f, fileBox.getPosition().y + fileBox.getSize().y / 4);
	text.setFillColor(sf::Color::White);
	window.draw(text);
}

void listFile(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[], int index, std::string fileName, std::string ext) {
	sf::RectangleShape fileBox(sf::Vector2f(window.getSize().x / 2, 30.f));
	fileBox.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	fileBox.setPosition(0.f + window.getSize().x / 2 * side, 200.f + index);

    sf::FloatRect iconBoxRect = fileBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	int i = index / 30;

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && fileBox.getPosition().y >= 200.f && fileBox.getPosition().y <= 660.f) {
        fileBox.setFillColor(selected[i] == 0 ? hoverrColor : clickeddColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			if (isDoubleClick(window)) {
				std::cout << "Double click!\n";
				if(ext == "") currentPath = currentPath + "/" + fileName;
				if (fileName[0] == '$') {
					std::cerr << "Acces denied!" << "\n";
					renderErrorWindow(window);
				}
				clearSelected(selected);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				std::cout << "Enter Pressed!\n";
				currentPath = currentPath + "/" + fileName;
				clearSelected(selected);
			}
			selected[i] = !selected[i];
            fileBox.setFillColor(selected[i] == 0 ? bgDarkColor : clickeddColor);
			/*
			for (int i = 0; i < 5; ++i)
				std::cout << selected[i] << " ";
			std::cout << "\n";
			*/
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
	else {
		fileBox.setFillColor(selected[i] == 0 ? bgDarkColor : clickeddColor);
	}
	window.draw(fileBox);
	///--------switch(fileExtension)
	if (fileName[0] == '$') renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/dangerfile_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == "" && fileName[0] != '$') renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/folder_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".exe") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/exe_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".zip") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/zip_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".png") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/png_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".jpg") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/jpg_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".txt") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/txt_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".dll") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/dll_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/unknown_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	
	///---------
	sf::Font& font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");
	sf::Text text;

	text.setFont(font);
	text.setCharacterSize(15);
	text.setString(fileName);
	text.setPosition(fileBox.getPosition().x + 40.f, fileBox.getPosition().y + fileBox.getSize().y / 4);
	text.setFillColor(sf::Color::White);
	window.draw(text);
	
}

void drawFilesFromDir(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, static bool selected[]) {
	int numberOfFiles = getNumberOfFilesFromDir(currentPath);
	int i;
	if (currentPath.size() > 3) {
		i = 1;
		drawBackFatherPath(window, side, view_mode, currentPath, selected);
	}
	else i = 0;
	try {
		for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
			listFile(window, side, view_mode, currentPath, selected, i * 30.f, entry.path().filename().string(), entry.path().extension().string());
			i++;
			if (i >= numberOfFiles)
				break;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception in listFile: " << e.what() << std::endl;
	}
}