#include <SFML/Graphics.hpp>
#include <filesystem>
#include <drawbars.h>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "usable.h"
#include "fileNavigator.h"

#define WINDOW_W 1280
#define WINDOW_H 720
using namespace std::filesystem;

bool loadedDrives = false;
bool loadedSize = false;
//bool openCMD = false, openNotepad = false;

sf::Color defaultDarkColor(51, 53, 54);
sf::Color hoverColor(7, 148, 224, 128);
sf::Color clickedColor(224, 20, 75);
sf::Color defaultLightColor(255, 255, 255);
sf::Color Gray(160, 160, 160);
sf::Color Dark_Gray(22, 22, 23);

void drawIconBoxesToolbar(sf::RenderWindow& window, const float index, bool& view_mode) {
    sf::RectangleShape iconBox(sf::Vector2f(70.f, 70.f));
    iconBox.setPosition(0.f + index, 0.f);
    iconBox.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);
    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        iconBox.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            iconBox.setFillColor(clickedColor);
            if (index == 70) {
                system("cmd /c start cmd");
                std::cout << "Opened CMD" << "\n";
                sf::sleep(sf::milliseconds(60));
            }
            else if (index == 140) {
                system("notepad");
                std::cout << "Opened Notepad" << "\n";
                sf::sleep(sf::milliseconds(60));
            }
            else if (index == 210) {
                view_mode == 0 ? view_mode = 1 : view_mode = 0;
                std::cout << "Changed view mode" << "\n";
                sf::sleep(sf::milliseconds(60));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        }
    }
    else {
        iconBox.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);
    }
    window.draw(iconBox);
}

void loadToolbar(sf::RenderWindow& window, bool& view_mode){
    sf::RectangleShape toolbar(sf::Vector2f(window.getSize().x, 70.f));
    toolbar.setPosition(0.f, 0.f);
    toolbar.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);

    window.draw(toolbar);
    for (int i = 0; i < 4; ++i)
        drawIconBoxesToolbar(window, i * 70.f, view_mode);
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/refresh_icon.png", window, sf::Vector2f(8.f, 10.f));
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/terminal_icon.png", window, sf::Vector2f(78.f, 10.f));
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/notepad_icon.png", window, sf::Vector2f(152.f, 10.f));
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/dark_light_mode_icon.png", window, sf::Vector2f(222.f, 10.f));

    sf::RectangleShape line(sf::Vector2f(window.getSize().x, 3.f));

    line.setFillColor(view_mode == 0 ? Gray : sf::Color::Black);
    line.setPosition(0.f, 70.f);
    window.draw(line);
}

void loadBetweenLine(sf::RenderWindow& window, bool& view_mode) {
    sf::RectangleShape lineBetween(sf::Vector2f(4.f, window.getSize().y - 70.f));
    lineBetween.setFillColor(view_mode == 0 ? Gray : sf::Color::Black);
    lineBetween.setPosition(window.getSize().x / 2, 70.f);
    window.draw(lineBetween);
}

void drawIconBoxesDisk(sf::RenderWindow& window, int index, bool &view_mode, std::string &currentDisk, std::string &currentPath, static bool selected[], int num, bool side, float &offsetY1, float &offsetY2) {
    sf::RectangleShape iconBox(sf::Vector2f(60.f, 60.f));
    iconBox.setPosition(0.f + index, 73.f);
    iconBox.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);

    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        iconBox.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            iconBox.setFillColor(clickedColor);
            if (index == 0) {
                currentDisk = currentPath = "C:/";
                offsetY1 = 200.f;
            }
            if (index == 60)
                currentDisk = currentPath = "D:/", offsetY1 = 200.f;
            if (index == 120)
                currentDisk = currentPath = "E:/", offsetY1 = 200.f;
            if (index == 180)
                currentDisk = currentPath = "F:/", offsetY1 = 200.f;
            if (index == 240)
                currentDisk = currentPath = "G:/", offsetY1 = 200.f;
            if (index == 300)
                currentDisk = currentPath = "H:/", offsetY2 = 200.f;;
            if (index == 360)
                currentDisk = currentPath = "I:/", offsetY2 = 200.f;;
            if (index == 0 + window.getSize().x / 2)
                currentDisk = currentPath = "C:/", offsetY2 = 200.f;
            if (index == 60 + window.getSize().x / 2)
                currentDisk = currentPath = "D:/", offsetY2 = 200.f;
            if (index == 120 + window.getSize().x / 2)
                currentDisk = currentPath = "E:/", offsetY2 = 200.f;
            if (index == 180 + window.getSize().x / 2)
                currentDisk = currentPath = "F:/", offsetY2 = 200.f;
            if (index == 240 + window.getSize().x / 2)
                currentDisk = currentPath = "G:/", offsetY2 = 200.f;
            if (index == 300 + window.getSize().x / 2)
                currentDisk = currentPath = "H:/", offsetY2 = 200.f;
            if (index == 360 + window.getSize().x / 2)
                currentDisk = currentPath = "I:/", offsetY2 = 200.f;
        
            selected[index - 60 * num + num - side * 640] = 1;
            if (selected[index - 60 * num + num - side * 640] == 1) {
                //std::cout << "ok" << " ";
                for (int i = 0; i < 8; ++i)
                    if (index - 60 * num + num - side * 640 != i)
                        selected[i] = 0;
            }
            /*
            for (int i = 0; i < 8; ++i)
                std::cout << selected[i] << " ";
            std::cout << index - 60 * num + num - side * 640 << "\n";
            */
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            
        }
    }
    else {
        if (selected[index - 60 * num + num - side * 640] == 1) iconBox.setFillColor(clickedColor);
        else iconBox.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);
    }
    window.draw(iconBox);
}

void loadBetweenLineDrivesSpace(sf::RenderWindow &window, bool side, bool& view_mode) {
    sf::RectangleShape line(sf::Vector2f(2.f, 60.f));
    line.setFillColor(view_mode == 0 ? Gray : sf::Color::Black);
    line.setPosition(window.getSize().x / 2 - 270.f + window.getSize().x / 2 * side, 73.f);
    window.draw(line);
}

void drawDiskSpace(std::string path, std::string space, sf::RenderWindow &window, bool side,bool& view_mode) {
    sf::Text text;
    sf::Font font;
     
    if (!font.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf")) {
        std::cerr << "Couldn't load the font quicksand for diskspace";
        return;
    }
    text.setFont(font);
    text.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
    text.setString(space);
    text.setCharacterSize(21);
    text.setPosition(window.getSize().x / 2 - 250.f + window.getSize().x / 2 * side, 90.f);
    window.draw(text);
    if (!loadedSize) {
        std::cout << "Loaded the space of the drive..." << "\n";
        loadedSize = true;
    }
}

void loadDiskSelection(sf::RenderWindow& window, int numberOfDrives, bool &view_mode, std::string &currentDisk, bool side, std::string &currentPath, static bool selected[], float &offsetY1, float &offsetY2) {
    sf::RectangleShape diskBar(sf::Vector2f(window.getSize().x / 2, 60.f));
    diskBar.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);
    diskBar.setPosition(0.f + window.getSize().x / 2 * side, 73.f);
    window.draw(diskBar);
    /*
    diskBar.setPosition(window.getSize().x / 2 + 4, 73.f);
    window.draw(diskBar);
    */
    for (int i = 0; i < numberOfDrives; ++i)
        drawIconBoxesDisk(window, (60.f * i) + window.getSize().x / 2 * side, view_mode, currentDisk, currentPath, selected, i, side, offsetY1, offsetY2);
    /*
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/c_drive.png", window, sf::Vector2f(8.f, 83.f));
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/d_drive.png", window, sf::Vector2f(68.f, 73.f));
    */
    loadBetweenLineDrivesSpace(window, side,view_mode);
    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/c_drive.png", window, sf::Vector2f(8.f + window.getSize().x / 2 * side, 83.f));
    for (int i = 1; i < numberOfDrives; ++i) {
        char c = 'c' + i;
        std::string path = "C:/PROIECT IP ORIGINAL/My Commander/assets/icons/" + std::string(1, c) + "_drive.png";
        if (!loadedDrives) {
            loadedDrives = true;
            std::cout << "Loaded drives.." << "\n";
        }
        renderIcon(path, window, sf::Vector2f(8.f + 60.f * i + window.getSize().x / 2 * side, 73.f));
    }
    drawDiskSpace(currentDisk, getSizeOfDrive(currentDisk), window, side, view_mode);
}

void loadPathBar(sf::RenderWindow& window, bool& view_mode, bool side, sf::Event &event, std::string &currentPath) {
    sf::RectangleShape pathBar(sf::Vector2f(window.getSize().x / 2, 40.f));
    pathBar.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);
    pathBar.setPosition(0.f + window.getSize().x / 2 * side, 135.f);
    window.draw(pathBar);
    sf::RectangleShape line(sf::Vector2f(window.getSize().x / 2, 2.f));
    line.setFillColor(view_mode == 0 ? Gray : sf::Color::Black);
    line.setPosition(0.f + window.getSize().x / 2 * side, 133.f);
    window.draw(line);
    line.setPosition(0.f + window.getSize().x / 2 * side, 175.f);
    window.draw(line);
    
    sf::Text pathText;
    sf::Font font;
    if (!font.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf")) {
        std::cerr << "Couldn't load the font quicksand for diskspace";
        return;
    }
    pathText.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
    pathText.setCharacterSize(24);
    pathText.setPosition(pathBar.getPosition().x + 7.f, pathBar.getPosition().y + 7.f);
    pathText.setFont(font);
    pathText.setString(currentPath);
    window.draw(pathText);

    sf::RectangleShape searchButton(sf::Vector2f(55.f, 40.f));
    sf::RectangleShape lineSearchButton(sf::Vector2f(2.f, 40.f));
    lineSearchButton.setFillColor(view_mode == 0 ? Gray : sf::Color::Black);
    lineSearchButton.setPosition(window.getSize().x / 2 * (side + 1) - 57.f, 136.f);

    searchButton.setFillColor(view_mode == 0 ? defaultLightColor : defaultDarkColor);
    searchButton.setPosition(window.getSize().x / 2 * (side + 1) - 55.f, 136.f);

    sf::FloatRect iconBoxRect = searchButton.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        searchButton.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            searchButton.setFillColor(clickedColor);
            renderSearchWindow(window, currentPath,view_mode);
            //renderErrorWindow(window);
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        }
    }
    else {
        searchButton.setFillColor(view_mode == 0 ? sf::Color::White : defaultDarkColor);
    }

    window.draw(searchButton);
    window.draw(lineSearchButton);

    renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png", window, sf::Vector2f(searchButton.getPosition().x + 9.f, searchButton.getPosition().y + 4.f));
    
}

void makeSortButton(sf::RenderWindow& window, bool& view_mode, bool side, std::string name, int index, int sort_buttons0[], int sort_buttons1[], folder files[])
{
    sf::RectangleShape iconBox(sf::Vector2f(160.f, 23.f));
    iconBox.setPosition(0.f + index * iconBox.getSize().x + window.getSize().x / 2 * side, 176.f);
    if (side == 1 && index == 0)
        iconBox.setPosition(4.f + index + window.getSize().x / 2 * side, 176.f);
    //?
    iconBox.setFillColor(view_mode == 0 ? Gray : Dark_Gray);

    sf::RectangleShape line(sf::Vector2f(1.f, 23.f));
    line.setFillColor(view_mode == 0 ? Gray : sf::Color::Black);
    line.setPosition(iconBox.getPosition().x + iconBox.getSize().x, 175.f);

    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        iconBox.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            iconBox.setFillColor(clickedColor);
            if (side == 0)
            {
                clearSelected(files);
                sort_buttons0[index]++;
                if (sort_buttons0[index] == 3) sort_buttons0[index] = 0;
            }
            if (side == 1)
            {
                clearSelected(files);
                sort_buttons1[index]++;
                if (sort_buttons1[index] == 3) sort_buttons1[index] = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    else {
        iconBox.setFillColor(view_mode == 0 ? Gray : Dark_Gray);
    }

    sf::Text buttonText;
    sf::Font font;
    if (!font.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf")) {
        std::cerr << "Couldn't load the font quicksand for diskspace";
        return;
    }
    
    if (side == 1) {
        if (sort_buttons1[index] == 0)  buttonText.setFillColor(sf::Color::White);
        else if (sort_buttons1[index] == 1)  buttonText.setFillColor(sf::Color::Blue);
        else if (sort_buttons1[index] == 2)  buttonText.setFillColor(sf::Color::Red);
    }
    else
    {
        if (sort_buttons0[index] == 0)  buttonText.setFillColor(sf::Color::White);
        else if (sort_buttons0[index] == 1)  buttonText.setFillColor(sf::Color::Blue);
        else if (sort_buttons0[index] == 2)  buttonText.setFillColor(sf::Color::Red);
    }
    buttonText.setFont(font);
    buttonText.setCharacterSize(18);
    buttonText.setString(name);
    //buttonText.setPosition(iconBox.getPosition().x + 45.f, iconBox.getPosition().y + 4.f);
    sf::Vector2f boxPosition(iconBox.getPosition().x, iconBox.getPosition().y);
    sf::Vector2f boxSize(iconBox.getSize().x, iconBox.getSize().y);
    sf::Vector2f textPosition;
    textPosition.x = boxPosition.x + (boxSize.x - buttonText.getGlobalBounds().width) / 2;
    textPosition.y = boxPosition.y + (boxSize.y - buttonText.getGlobalBounds().height) / 2 - 5.f;
    buttonText.setPosition(textPosition);
    window.draw(iconBox);
    window.draw(buttonText);
    window.draw(line);
}

void loadSortBar(sf::RenderWindow& window, bool& view_mode, bool side, int sort_buttons0[], int sort_buttons1[], folder files[]) {
    sf::RectangleShape sortBar(sf::Vector2f(window.getSize().x / 2, 25.f));
    sortBar.setFillColor(view_mode == 0 ? Gray : Dark_Gray);
    sortBar.setPosition(0.f + window.getSize().x / 2 * side, 175.f);
    if (side == 1)
        sortBar.setPosition(0.f + window.getSize().x / 2 + 4.f, 175.f);

    window.draw(sortBar);
    makeSortButton(window, view_mode, side, "Name", 0, sort_buttons0, sort_buttons1, files);
    makeSortButton(window, view_mode, side, "Ext", 1, sort_buttons0, sort_buttons1, files);
    makeSortButton(window, view_mode, side, "Date", 2, sort_buttons0, sort_buttons1, files);
    makeSortButton(window, view_mode, side, "Size", 3, sort_buttons0, sort_buttons1, files);
}