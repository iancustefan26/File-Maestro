#include "fileNavigator.h"
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <sstream>
#include "filesize.h"
#include "drawbars.h"
#include "usable.h"
#include "textureCache.h"
#include "filesize.h"
#include "sorts.h"
#include "buttons.h"

#define _CRT_SECURE_NO_WARNINGS


sf::Color bgDarkColor(89, 87, 87);
sf::Color defaulttDarkColor(51, 53, 54);
sf::Color bgLightColor(199, 199, 199);
sf::Color Grayish(160, 160, 160);
sf::Color hoverrColor(7, 148, 224, 128);
sf::Color clickeddColor(224, 20, 75);

void clearSelected(folder files[]) {
	for (int i = 0; i < 205; ++i)
		files[i].selected = 0;
}

bool canOpenFolder(std::string folderPath) {
	try {
		// Check if the folder exists
		if (exists(folderPath) && is_directory(folderPath)) {
			std::cout << "Folder exists. Checking permissions..." << std::endl;

			// Iterate through the contents of the folder
			for (const auto& entry : directory_iterator(folderPath)) {
				// Do nothing; just iterating to check permissions
			}

			std::cout << "Folder can be opened. Permissions are sufficient." << std::endl;
			return true;
		}
		else {
			std::cerr << "Folder does not exist or is not a valid folder path." << std::endl;
			return false;
		}
	}
	catch (const filesystem_error& e) {
		// Handle exception
		std::cerr << "Error checking folder: " << e.what() << std::endl;
		return false;
	}
	catch (...) {
		// Handle unexpected exceptions
		std::cerr << "Unexpected error checking folder." << std::endl;
		return false;
	}
}

std::string getFileLastModifiedTime(const std::string& filePath) {
	try {
		// Convert the file path to std::filesystem::path
		path file(filePath);

		// Get the last modification time of the file
		auto lastWriteTime = last_write_time(file);

		// Convert the file_time_type to a system_clock::time_point
		auto timePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - file_time_type::clock::now() + std::chrono::system_clock::now());

		// Convert the time_point to a time_t for easy printing
		std::time_t modifiedTime = std::chrono::system_clock::to_time_t(timePoint);

		// Convert time_t to string
		std::stringstream ss;

		// Use localtime_s to avoid deprecated warning
		std::tm timeInfo;
		if (localtime_s(&timeInfo, &modifiedTime) == 0) {
			ss << std::put_time(&timeInfo, "%c");
		}
		
		//eliminate the seconds
		std::string newSS;
		newSS = ss.str();
		newSS = newSS.substr(0, newSS.size() - 3);


		return newSS;
	}
	catch (const std::exception& e) {
		// Handle exceptions (e.g., file not found)
		std::cerr << "Error: " << e.what() << std::endl;
		return ""; // Return an empty string on error
	}
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

void drawBackFatherPath(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath, folder files[]) {
	sf::RectangleShape fileBox(sf::Vector2f(window.getSize().x / 2, 30.f));
	fileBox.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	fileBox.setPosition(0.f + window.getSize().x / 2 * side, 200.f);
	static bool select = 0;
	sf::FloatRect iconBoxRect = fileBox.getGlobalBounds();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	int i = 0;

	if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && fileBox.getPosition().y >= 200.f && fileBox.getPosition().y <= 660.f) {
		fileBox.setFillColor(files[i].selected == 0 ? hoverrColor : clickeddColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (isDoubleClick(window)) {
				std::cout << "Double click!\n";
				size_t lastSlashPos = currentPath.find_last_of('/');
				currentPath = currentPath.substr(0, lastSlashPos);
				if (currentPath.size() < 3)
					currentPath += "/";
				clearSelected(files);
			}
			select = !select;
			fileBox.setFillColor(select == 0 ? bgDarkColor : clickeddColor);
			/*
			for (int i = 0; i < 5; ++i)
				std::cout << selected[i] << " ";
			std::cout << "\n";
			*/
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	else {
		fileBox.setFillColor(select == 0 ? view_mode == 0 ? bgLightColor : bgDarkColor : clickeddColor);
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
	text.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
	window.draw(text);
}

void create_files(std::string& currentPath, folder files[],int k)
{
	int numberOfFiles = getNumberOfFilesFromDir(currentPath);
	int i=0;
	
	try {
		for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
			files[i].name = entry.path().filename().string();
			files[i].extension = entry.path().extension().string();
			files[i].size = std::filesystem::file_size(entry.path());
			
			try {
				path file(currentPath);
				auto lastWriteTime = last_write_time(file);
				auto timePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - file_time_type::clock::now() + std::chrono::system_clock::now());
				std::time_t modifiedTime = std::chrono::system_clock::to_time_t(timePoint);
				files[i].date = modifiedTime;
			}
			catch (const std::exception& e) {
				std::cerr << "Error getting last modification time for " << currentPath << ": " << e.what() << std::endl;
			}
			files[i].path_file = replaceBackslashes(entry.path().string());
			i++;
			if (i > numberOfFiles)
				break;
			
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception in listFile: " << e.what() << std::endl;
	}
}

void listFile(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath,  int index, std::string fileName, std::string ext, sf::Event& event, bool& scrolled, float& offsetY,folder files[], int ind) {
	sf::RectangleShape fileBox(sf::Vector2f(window.getSize().x / 2, 30.f));
	fileBox.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	fileBox.setPosition(0.f + window.getSize().x / 2 * side, offsetY + index);

	sf::FloatRect iconBoxRect = fileBox.getGlobalBounds();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	int i = index / 30 - ind;

	if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && fileBox.getPosition().y >= 200.f && fileBox.getPosition().y <= 660.f) {
		fileBox.setFillColor(files[i].selected == 0 ? hoverrColor : clickeddColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			if (isDoubleClick(window)) {
				std::cout << "Double click!\n";
				if (fileName[0] == '$') {
					std::cerr << "Acces denied!" << "\n";
					renderErrorWindow(window, view_mode);
				}
				else if (ext == "") {
					if (canOpenFolder(files[i].path_file)) {

						currentPath = files[i].path_file, offsetY = 200.f, clearSelected(files);

						
					}
					else {
						std::cerr << "Acces denied!" << "\n";
						renderErrorWindow(window, view_mode);
					}
				}
				else {
					std::string filePath = files[i].path_file;
					std::string command = "start \"\" \"" + filePath + "\""; ///because of spaces in file name, the shell might not recognize
					std::system(command.c_str());
				}
				clearSelected(files);
			}
			files[i].selected = !files[i].selected;
			fileBox.setFillColor(files[i].selected == 0 ? view_mode == 0 ? bgLightColor : bgDarkColor : clickeddColor);
			/*
			for (int i = 0; i < 5; ++i)
				std::cout << selected[i] << " ";
			std::cout << "\n";
			*/
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	else {
		fileBox.setFillColor(files[i].selected == 0 ? view_mode == 0 ? bgLightColor : bgDarkColor : clickeddColor);
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
	else if (ext == ".mp3") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/music_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".mp4") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/video_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else if (ext == ".mov") renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/video_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));
	else renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/file_navigator/unknown_icon.png", window, sf::Vector2f(10.f + window.getSize().x / 2 * side, fileBox.getPosition().y + fileBox.getSize().y / 6));

	///---------
	sf::Font& font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");
	sf::Text text;

	text.setFont(font);
	text.setCharacterSize(15);
	text.setString(fileName);
	text.setPosition(fileBox.getPosition().x + 40.f, fileBox.getPosition().y + fileBox.getSize().y / 4);
	text.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
	window.draw(text);

	sf::Text extension;
	extension.setCharacterSize(15);
	extension.setString(ext == "" ? "<DIR>" : ext);
	extension.setFont(font);
	extension.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
	extension.setPosition(0.f + window.getSize().x / 2 * side + 233.f, fileBox.getPosition().y + fileBox.getSize().y / 4);
	window.draw(extension);

	sf::Text date;
	date.setCharacterSize(12);
	date.setString(getFileLastModifiedTime(files[i].path_file));
	date.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
	date.setFont(font);
	date.setPosition(0.f + window.getSize().x / 2 * side + 350.f, fileBox.getPosition().y + fileBox.getSize().y / 4);
	window.draw(date);

	if (ext != "") {
		//std::string stringSize = std::to_string(file_size(currentPath + "/" + fileName) / 1024) + " KB";
		sf::Text size;
		size.setCharacterSize(14);
		size.setFont(font);
		size.setString(compressSize(file_size(files[i].path_file)));
		size.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
		size.setPosition(0.f + window.getSize().x / 2 * side + 500.f, fileBox.getPosition().y + fileBox.getSize().y / 4);
		window.draw(size);
	}
}

bool mouseOnFiles(sf::RenderWindow& window, float minX, float minY, float maxX, float maxY) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f mouseCoords = window.mapPixelToCoords(mousePosition);

	if (mouseCoords.x >= minX && mouseCoords.x <= maxX &&
		mouseCoords.y >= minY && mouseCoords.y <= maxY) {
		return true;
	}
	return false;
}

void drawFilesFromDir(sf::RenderWindow& window, bool side, bool& view_mode, std::string& currentPath,  sf::Event& event, bool& scrolled, float& offsetY, int sort_buttons0[], int sort_buttons1[],folder files1[],folder files2[]) {
	
	int numberOfFiles = getNumberOfFilesFromDir(currentPath);
	int noFI = numberOfFiles;
	int inde=0;
	int index = 0;
	if (currentPath.size() > 3) {
		inde = 1;
		index = 1;
		if(side==0)drawBackFatherPath(window, side, view_mode, currentPath, files1);
		else drawBackFatherPath(window, side, view_mode, currentPath, files2);
	}
	else inde = 0, index = 0, numberOfFiles--;
	if(side==0)create_files(currentPath, files1,0);
	else create_files(currentPath, files2, 0);
	
	for (int i = 0; i < 4; i++)
	{
		if (side == 0)
		{
			choose_sort(sort_buttons0[i], i, files1, noFI,0);
		}
		if (side == 1)
		{
			choose_sort(sort_buttons1[i], i, files2, noFI,0);
		}
	}
	
	/*
	*/
	for (int i = index; i <= numberOfFiles;i++) {
			//offsetY = 200.f;
			if (event.type == sf::Event::MouseWheelScrolled && mouseOnFiles(window, 0.f, 200.f, 1280.f, 675.f)) {
				if((side == 0 && mouseOnFiles(window, 0, 200.f, 635.f, 675.f)) || (side == 1 && mouseOnFiles(window, 636.f, 200.f, 1280.f, 675.f)))
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					// Scrolling up
					if (event.mouseWheelScroll.delta > 0) {
						// Handle upward scroll
						if (!scrolled) {
							//std::cout << "Scroll Up\n";
							scrolled = true;
							if (currentPath.length() <= 4) {
								if (offsetY < 200.f)
									offsetY += 50.f;
							}
							else if (offsetY < 200.f)
								offsetY += 50.f;
						}
					}
					// Scrolling down
					else if (event.mouseWheelScroll.delta < 0) {
						// Handle downward scroll
						if (!scrolled) {
							//std::cout << "Scroll Down\n";
							//offsetY -= 50.f;
							scrolled = true;
							if(offsetY >  200.f - 20.f * numberOfFiles)
								offsetY -= 50.f;
						}
					}
					else scrolled = false;
				}
			}
			else if (!window.pollEvent(event))
				scrolled = false;

			if(side==0)listFile(window, side, view_mode, currentPath, i * 30.f, files1[i - index].name, files1[i - index].extension, event, scrolled, offsetY,files1, index);
			else listFile(window, side, view_mode, currentPath, i * 30.f, files2[i - index].name, files2[i - index].extension, event, scrolled, offsetY, files2, index);
		}
	

}

void readyToWrite(sf::RectangleShape& inputBar, sf::RenderWindow& window, static bool selected[], int bar, sf::Text& text, std::string &string, std::string &currentPath,bool& view_mode) {

	sf::FloatRect iconBoxRect = inputBar.getGlobalBounds();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			selected[bar] = !selected[bar];
			if (selected[bar] == 1)
				if (bar == 0) {
					selected[1] = 0;
					text.setPosition(sf::Vector2f(inputBar.getPosition().x + 5.f, inputBar.getPosition().y + 5.f));
					string = "";
					text.setString(string);
				}
				else { 
					selected[0] = 0;
					text.setPosition(sf::Vector2f(inputBar.getPosition().x + 5.f, inputBar.getPosition().y + 5.f));
					string = currentPath;
					text.setString(string);
				}
			inputBar.setFillColor(selected[bar] == 1 ? view_mode == 0 ? bgLightColor : bgDarkColor : Grayish);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	else {
		inputBar.setFillColor(selected[bar] == 1 ? view_mode == 0 ? bgLightColor : bgDarkColor : Grayish);
	}
}

void renderSearchWindow(sf::RenderWindow& window, std::string& currentPath, bool& view_mode) {
	sf::RenderWindow searchWindow(sf::VideoMode(500.f, 300.f), "Search Window");
	searchWindow.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
		sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));

	sf::Image icon;
	sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

	if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png")) {
		searchWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		std::cout << "Loaded window icon..." << "\n";
	}
	else {
		std::cerr << "Error when loading the window icon!" << "\n";
		return;
	}

	sf::Text title1;
	title1.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
	title1.setCharacterSize(20);
	title1.setFont(font);
	title1.setPosition(160.f, 10.f);
	std::string title1Text = "Search file by name:";
	title1.setString(title1Text);

	sf::Text title2;
	title2.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
	title2.setCharacterSize(20);
	title2.setFont(font);
	title2.setPosition(160.f, 117.f);
	title1Text = "or Change the path:";
	title2.setString(title1Text);

	sf::RectangleShape searchIcon(sf::Vector2f(50.f, 50.f));
	searchIcon.setPosition(221.f, 230.f);
	searchIcon.setFillColor(view_mode == 0 ? sf::Color::White : defaulttDarkColor);

	sf::RectangleShape inputBar1(sf::Vector2f(380.f, 35.f));
	inputBar1.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	inputBar1.setPosition(60.f, 50.f);

	sf::RectangleShape inputBar2(sf::Vector2f(380.f, 35.f));
	inputBar2.setFillColor(view_mode == 0 ? bgLightColor : bgDarkColor);
	inputBar2.setPosition(60.f, 150.f);


	sf::Text inputText;
	inputText.setFont(font);
	inputText.setCharacterSize(18);
	inputText.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
	inputText.setPosition(65.f, 155.f);
	std::string inputString = currentPath + "/";
	inputText.setString(inputString);

	static bool selectedBar[2] = { 0, 0 };

	while (searchWindow.isOpen()) {
		sf::Event event;
		while (searchWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				searchWindow.close();
				return;
			}
			readyToWrite(inputBar1, searchWindow, selectedBar, 0, inputText, inputString, currentPath,view_mode);
			readyToWrite(inputBar2, searchWindow, selectedBar, 1, inputText, inputString, currentPath,view_mode);
				if (event.type == sf::Event::TextEntered && (selectedBar[0] == 1 || selectedBar[1] == 1)) {
					if (event.text.unicode < 128 && event.text.unicode != 8) {
						inputString += static_cast<char>(event.text.unicode);
					}
					// Handle backspace
					else if (event.text.unicode == 8 && !inputString.empty()) {
						inputString.pop_back();
					}
					inputText.setString(inputString);
				}
		}
		searchWindow.clear(view_mode == 0 ? sf::Color::White : defaulttDarkColor);
		searchWindow.draw(searchIcon);
		sf::FloatRect iconBoxRect = searchIcon.getGlobalBounds();
		sf::Vector2i mousePosition = sf::Mouse::getPosition(searchWindow);

		sf::Cursor arrowCursor;
		sf::Cursor handCursor;
		if (!arrowCursor.loadFromSystem(sf::Cursor::Arrow)) {
			std::cerr << "Error loading mouse pointer\n";
			return;
		}
		if (!handCursor.loadFromSystem(sf::Cursor::Hand)) {
			std::cerr << "Error loading mouse pointer\n";
			return;
		}
		if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
			searchWindow.setMouseCursor(handCursor);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (selectedBar[0] == 1)
					searchForFile(currentPath, inputString, searchWindow,view_mode);
				else
					changePath(currentPath, inputString, searchWindow, view_mode);
			}
		}
		else {
			searchWindow.setMouseCursor(arrowCursor);
		}
		searchWindow.draw(inputBar1);
		searchWindow.draw(inputBar2);
		renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png", searchWindow, sf::Vector2f(searchWindow.getSize().x / 2 - 20.f, 240.f));
		searchWindow.draw(inputText);
		searchWindow.draw(title1);
		searchWindow.draw(title2);
		searchWindow.display();
	}
}

std::string toLowercase(const std::string input) {
	std::string result = input;
	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
		return std::tolower(c);
		});
	return result;
}

std::string replaceBackslashes(const std::string& inputString) {
	std::string resultString = inputString;
	size_t found = resultString.find("\\");

	while (found != std::string::npos) {
		resultString.replace(found, 1, "/");
		found = resultString.find("\\", found + 1);
	}

	return resultString;
}

std::string removeLastPathComponent(const std::string& filePath) {
	size_t lastSlash = filePath.find_last_of("/\\");

	if (lastSlash != std::string::npos) {
		return filePath.substr(0, lastSlash);
	}

	return filePath;
}

std::string removeLastExtComponent(const std::string& filePath) {
	size_t lastDot = filePath.find_last_of(".");

	if (lastDot != std::string::npos) {
		return filePath.substr(0, lastDot);
	}

	return filePath;
}

bool containsSubstring(const std::string& mainString, const std::string& substring) {
	return mainString.find(substring) != std::string::npos;
}

void searchForFile(std::string& currentPath, std::string inputString, sf::RenderWindow& window,bool& view_mode) {
	try {
		for (const auto& entry : recursive_directory_iterator(currentPath)) {
			std::string filename = entry.path().filename().string();
			//std::cout << filename << "\n";
			if (filename[0] == '$')
				continue;
			else if(is_directory(entry.path().string()) && !canOpenFolder(entry.path().string()))
				continue;
			else if (is_directory(entry.path().string())) {
				if (containsSubstring(toLowercase(entry.path().filename().string()), toLowercase(inputString))) {
					currentPath = replaceBackslashes(entry.path().string());
					//std::cout << toLowercase(entry.path().filename().string()) << "\n";
					window.close();
					return;
					}
				}
			else {
				if(containsSubstring(toLowercase(removeLastExtComponent(filename)), toLowercase(inputString))){
					std::string filePath = removeLastPathComponent(replaceBackslashes(entry.path().string()));
					std::cout << filePath << "\n";
					currentPath = filePath;
					window.close();
					return;
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
	renderErrorWindow(window,view_mode);
}


void changePath(std::string& currentPath, std::string& inputString, sf::RenderWindow& window, bool &view_mode) {
	if(is_directory(replaceBackslashes(inputString))){
		currentPath = replaceBackslashes(inputString);
		window.close();
		return;
	}
	else
		renderErrorWindow(window, view_mode);
}