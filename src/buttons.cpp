#include <SFML/Graphics.hpp>
#include "buttons.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <thread>
#include "filesize.h"
#include "fileNavigator.h"
#include "usable.h"
#include "drawbars.h"

using namespace std::filesystem;

sf::Color bbgDarkColor(89, 87, 87);
sf::Color bdefaulttDarkColor(51, 53, 54);
sf::Color bbgLightColor(199, 199, 199);
sf::Color bGrayish(160, 160, 160);
sf::Color bhoverrColor(7, 148, 224, 128);
sf::Color bclickeddColor(224, 20, 75);

void deleteFiles(folder files[], std::string currentPath,static bool Selected[]) {
    int i = 0;
    std::cout << "\n";
    for (const auto& entry : directory_iterator(currentPath)) {
        if (Selected[i]) {
            std::string filePath = replaceBackslashes(entry.path().string());
            try {
                // Check if the file exists before attempting to delete
                if (exists(filePath)) {
                    std::cout << filePath << "\n";
                    remove_all(filePath);
                    std::cout << "File deleted successfully.\n";
                }
                else {
                    std::cout << "File not found.\n";
                }
            }
            catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error deleting file: " << e.what() << '\n';

            }
        }
        i++;
    }
    clearSelected(files,Selected);
}

void open(std::string &currentPath, folder files[], sf::RenderWindow& window, bool& view_mode,static bool Selected[]) {
    int ct = 0;
    for (int i = 0; i < 204; ++i)
        if (Selected[i])
            ct++;
    if (ct != 1)
        return;
    ct = 0;
    for (const auto& entry : directory_iterator(currentPath)) {
        if(Selected[ct])
            if (is_regular_file(entry.path().string())) {
                std::string filePath = replaceBackslashes(entry.path().string());
                std::string command = "start \"\" \"" + filePath + "\""; ///because of spaces in file name, the shell might not recognize
                std::system(command.c_str());
                return;
            }
            else {
                std::string fileName = entry.path().filename().string();
                std::cout << fileName << "\n";
                if (fileName[0] == '$') {
                    renderErrorWindow(window, view_mode);
                    return;
                }
                else {
                    std::cout << "Da";
                    currentPath = files[ct].path_file;
                    return;
                }
            }
            
        ct++;
    }
}

void copyFilesOn(folder files[], std::string destination, std::string currentPath, sf::RenderWindow& window, bool& view_mode,static bool Selected[])
{
    int i = 0;
    if (!exists(destination)) {
        std::cerr << "Destination directory doesn't exist ." << std::endl;
        return ;
    }
    for (const auto& entry : directory_iterator(currentPath)) {
        const path& sourcePath = entry.path(); 
        const path destPath = destination/ sourcePath.filename();
        if (Selected[i])
        {
            try {
                copy_file(sourcePath, destPath, copy_options::overwrite_existing);
                std::cout << "Copied: " << sourcePath << " to " << destPath << std::endl;
            }
            catch (const filesystem_error& e) {
                std::cerr << "Error copying file: " << e.what() << std::endl;
                renderErrorWindow(window, view_mode);
                return;
            }
        }
        i++;
    }
    window.close();
    sf::RenderWindow win(sf::VideoMode(500.f, 150.f), "Copied");
    win.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
        sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));
    sf::Image icon;
    sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

    if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png")) {
       win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
    title1.setPosition(160.f, 50.f);
    std::string title1Text = "Files copied succesfully";
    title1.setString(title1Text);
    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
                return;
            }
        }
            win.clear(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);
            win.draw(title1);
            win.display();
        }
}


void renderF4_COPY(sf::RenderWindow& window, std::string& currentPath, bool& view_mode, folder files[],static bool Selected[]) {
    sf::RenderWindow F4_Window(sf::VideoMode(500.f, 150.f), "CopyFile");
    F4_Window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
        sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));

    sf::Image icon;
    sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

    if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png")) {
        F4_Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
    std::string title1Text = "Copy the files on:";
    title1.setString(title1Text);

    sf::RectangleShape F4_Icon(sf::Vector2f(50.f, 50.f));
    F4_Icon.setPosition(221.f, 100.f);
    F4_Icon.setFillColor(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);

    sf::RectangleShape inputBar1(sf::Vector2f(380.f, 35.f));
    inputBar1.setFillColor(view_mode == 0 ? bbgLightColor : bbgDarkColor);
    inputBar1.setPosition(60.f, 50.f);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
    inputText.setPosition(65.f, 55.f);
    std::string inputString = currentPath;
    inputText.setString(inputString);

    static bool selectedBar = 0;

    while (F4_Window.isOpen()) {
        sf::Event event;
        while (F4_Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                F4_Window.close();
                return;
            }
            sf::FloatRect iconBoxRect = inputBar1.getGlobalBounds();
            sf::Vector2i mousePosition = sf::Mouse::getPosition(F4_Window);

            if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (selectedBar == 0)selectedBar = 1;
                    else selectedBar = 0;
                    inputBar1.setFillColor(selectedBar == 1 ? view_mode == 0 ? bbgLightColor : bbgDarkColor : bGrayish);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            else {
                inputBar1.setFillColor(selectedBar == 1 ? view_mode == 0 ? bbgLightColor : bbgDarkColor : bGrayish);
            }
            if (event.type == sf::Event::TextEntered && (selectedBar == 1)) {
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
        F4_Window.clear(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);
        F4_Window.draw(F4_Icon);
        sf::FloatRect iconBoxRect = F4_Icon.getGlobalBounds();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(F4_Window);

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
            F4_Window.setMouseCursor(handCursor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (selectedBar == 1)
                {
                    copyFilesOn(files, inputText.getString(), currentPath,F4_Window,view_mode,Selected);
                }
            }
        }
        else {
            F4_Window.setMouseCursor(arrowCursor);
        }
        F4_Window.draw(inputBar1);
        renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png", F4_Window, sf::Vector2f(F4_Window.getSize().x / 2 - 20.f, 100.f));
        F4_Window.draw(inputText);
        F4_Window.draw(title1);
        F4_Window.display();
    }
}


void MoveFilesTo(folder files[], std::string destination, std::string currentPath, sf::RenderWindow& window, bool& view_mode,static bool Selected[])
{
    int i = 0;
    if (!exists(destination)) {
        std::cerr << "Destination directory doesn't exist ." << std::endl;
        std::cout << destination << "\n";
        return;
    }
    for (const auto& entry : directory_iterator(currentPath)) {
        const path& sourcePath = entry.path();
        const path destPath = destination / sourcePath.filename();
        if (Selected[i])
        {
            try {
                rename(sourcePath, destPath);
                std::cout << "Moved: " << sourcePath << " to: " << destPath << std::endl;
            }
            catch (const filesystem_error& e) {
                std::cerr << "Error :" << e.what() << std::endl;
                renderErrorWindow(window, view_mode);
                return;
            }
        }
        i++;
    }
    window.close();
    sf::RenderWindow win(sf::VideoMode(500.f, 150.f), "Moved");
    win.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
        sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));
    sf::Image icon;
    sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

    if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png")) {
        win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
    title1.setPosition(160.f, 50.f);
    std::string title1Text = "Files moved succesfully";
    title1.setString(title1Text);
    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
                return;
            }
        }
        win.clear(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);
        win.draw(title1);
        win.display();
    }
}


void renderF5_MOVE(sf::RenderWindow& window, std::string& currentPath, bool& view_mode,folder files[],static bool Selected[]) {
    sf::RenderWindow F5_Window(sf::VideoMode(500.f, 150.f), "MoveFile");
    F5_Window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
        sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));

    sf::Image icon;
    sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

    if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png")) {
        F5_Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
    std::string title1Text = "Move files to:";
    title1.setString(title1Text);

    sf::RectangleShape F5_Icon(sf::Vector2f(50.f, 50.f));
    F5_Icon.setPosition(221.f, 100.f);
    F5_Icon.setFillColor(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);

    sf::RectangleShape inputBar1(sf::Vector2f(380.f, 35.f));
    inputBar1.setFillColor(view_mode == 0 ? bbgLightColor : bbgDarkColor);
    inputBar1.setPosition(60.f, 50.f);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
    inputText.setPosition(65.f, 55.f);
    std::string inputString = currentPath;
    inputText.setString(inputString);

    static bool selectedBar = 0;

    while (F5_Window.isOpen()) {
        sf::Event event;
        while (F5_Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                F5_Window.close();
                return;
            }
            sf::FloatRect iconBoxRect = inputBar1.getGlobalBounds();
            sf::Vector2i mousePosition = sf::Mouse::getPosition(F5_Window);

            if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (selectedBar == 0)selectedBar = 1;
                    else selectedBar = 0;
                    inputBar1.setFillColor(selectedBar == 1 ? view_mode == 0 ? bbgLightColor : bbgDarkColor : bGrayish);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            else {
                inputBar1.setFillColor(selectedBar == 1 ? view_mode == 0 ? bbgLightColor : bbgDarkColor : bGrayish);
            }
            if (event.type == sf::Event::TextEntered && (selectedBar == 1)) {
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
        F5_Window.clear(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);
        F5_Window.draw(F5_Icon);
        sf::FloatRect iconBoxRect = F5_Icon.getGlobalBounds();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(F5_Window);

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
            F5_Window.setMouseCursor(handCursor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (selectedBar == 1)
                {
                    MoveFilesTo(files, inputText.getString(), currentPath, F5_Window, view_mode,Selected);
                }
            }
        }
        else {
            F5_Window.setMouseCursor(arrowCursor);
        }
        F5_Window.draw(inputBar1);
        renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png", F5_Window, sf::Vector2f(F5_Window.getSize().x / 2 - 20.f, 100.f));
        F5_Window.draw(inputText);
        F5_Window.draw(title1);
        F5_Window.display();
    }
}


void renderF6_NEW(sf::RenderWindow& window, std::string& currentPath, bool& view_mode) {
    sf::RenderWindow F6_Window(sf::VideoMode(500.f, 150.f), "NewFile");
    F6_Window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
        sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));

    sf::Image icon;
    sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

    if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png")) {
        F6_Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
    std::string title1Text = "New file name:";
    title1.setString(title1Text);

    sf::RectangleShape F6_Icon(sf::Vector2f(50.f, 50.f));
    F6_Icon.setPosition(221.f, 100.f);
    F6_Icon.setFillColor(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);

    sf::RectangleShape inputBar1(sf::Vector2f(380.f, 35.f));
    inputBar1.setFillColor(view_mode == 0 ? bbgLightColor : bbgDarkColor);
    inputBar1.setPosition(60.f, 50.f);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(view_mode == 0 ? sf::Color::Black : sf::Color::White);
    inputText.setPosition(65.f, 55.f);
    std::string inputString ="";
    inputText.setString(inputString);

    static bool selectedBar = 0;

    while (F6_Window.isOpen()) {
        sf::Event event;
        while (F6_Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                F6_Window.close();
                return;
            }
            sf::FloatRect iconBoxRect = inputBar1.getGlobalBounds();
            sf::Vector2i mousePosition = sf::Mouse::getPosition(F6_Window);

            if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (selectedBar == 0)selectedBar = 1;
                    else selectedBar = 0;
                    inputBar1.setFillColor(selectedBar == 1 ? view_mode == 0 ? bbgLightColor : bbgDarkColor : bGrayish);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            else {
                inputBar1.setFillColor(selectedBar == 1 ? view_mode == 0 ? bbgLightColor : bbgDarkColor : bGrayish);
            }
            if (event.type == sf::Event::TextEntered && (selectedBar == 1)) {
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
        F6_Window.clear(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);
        F6_Window.draw(F6_Icon);
        sf::FloatRect iconBoxRect = F6_Icon.getGlobalBounds();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(F6_Window);

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
            F6_Window.setMouseCursor(handCursor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (selectedBar == 1)
                {
                    createDirInPath(currentPath, inputText.getString());
                    F6_Window.close();
                    sf::RenderWindow win(sf::VideoMode(500.f, 150.f), "Created");
                    win.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400 / 2,
                        sf::VideoMode::getDesktopMode().height / 2 - 300 / 2));
                    sf::Image icon;
                    sf::Font font = getFont("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf");

                    if (icon.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png")) {
                        win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
                    title1.setPosition(160.f, 50.f);
                    std::string title1Text = "File created succesfully";
                    title1.setString(title1Text);
                    while (win.isOpen()) {
                        sf::Event event;
                        while (win.pollEvent(event)) {
                            if (event.type == sf::Event::Closed) {
                                win.close();
                                return;
                            }
                        }
                        win.clear(view_mode == 0 ? sf::Color::White : bdefaulttDarkColor);
                        win.draw(title1);
                        win.display();
                    }
                }
            }
        }
        else {
            F6_Window.setMouseCursor(arrowCursor);
        }
        F6_Window.draw(inputBar1);
        renderIcon("C:/PROIECT IP ORIGINAL/My Commander/assets/icons/search_icon.png", F6_Window, sf::Vector2f(F6_Window.getSize().x / 2 - 20.f, 100.f));
        F6_Window.draw(inputText);
        F6_Window.draw(title1);
        F6_Window.display();
    }
}


void makeButton(sf::RenderWindow& window, std::string name, int index,bool& view_mode, std::string &currentPath, folder files[],sf::Event event,static bool Selected[]) {
    sf::Color default_dark_Color(51, 53, 54);
    sf::Color default_light_Color(160, 160, 160);
    sf::Color hoverColor(7, 148, 224, 128);
    sf::Color clickedColor(224, 20, 75);

    sf::RectangleShape iconBox(sf::Vector2f(213.f, 40.f));
    iconBox.setPosition(0.f + index, 680.f);
    iconBox.setFillColor(view_mode == 0 ? default_light_Color : default_dark_Color);

    sf::RectangleShape line(sf::Vector2f(1.f, 40.f));
    line.setFillColor(sf::Color::Black);
    line.setPosition(iconBox.getPosition().x + 213.f, 680.f);

    sf::FloatRect iconBoxRect = iconBox.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (iconBoxRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        iconBox.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            iconBox.setFillColor(clickedColor);

            if (name == "F6 New Folder")
            {
                renderF6_NEW(window, currentPath, view_mode);
            }
            if (name == "F7 Delete")
                deleteFiles(files, currentPath,Selected);
            if (name == "F3 Open")
                open(currentPath, files, window, view_mode,Selected);
            if (name == "Alt+F4 Exit")
                window.close();
            if (name == "F4 Copy")
            {
                renderF4_COPY(window, currentPath, view_mode,files,Selected);
            }
            if (name == "F5 Move")
            {
                renderF5_MOVE(window, currentPath, view_mode, files,Selected);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }                   
    }
    else {
        
        iconBox.setFillColor(view_mode == 0 ? sf::Color::White : default_dark_Color);
    }
    /*if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F4 && event.key.alt) {
            window.close();
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F5 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            renderF5_MOVE(window, currentPath, view_mode, files, Selected);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F3 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            open(currentPath, files, window, view_mode, Selected);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F6 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            renderF6_NEW(window, currentPath, view_mode);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F7 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            deleteFiles(files, currentPath, Selected);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F4 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            renderF4_COPY(window, currentPath, view_mode, files, Selected);
        }
    }*/
    sf::Text buttonText;
    sf::Font font;
    if (!font.loadFromFile("C:/PROIECT IP ORIGINAL/My Commander/assets/fonts/aovel_sans.ttf")) {
        std::cerr << "Couldn't load the font quicksand for diskspace";
        return;
    }
    buttonText.setFillColor(view_mode == 1 ? sf::Color::White : sf::Color::Black);
    buttonText.setFont(font);
    buttonText.setCharacterSize(24);
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

void drawCommandButtons(sf::RenderWindow& window,bool& view_mode, std::string &currentPath, folder files[],sf::Event event,static bool Selected[]) {
	std::vector<std::string> buttonNames;
	buttonNames.push_back("F3 Open");
	buttonNames.push_back("F4 Copy");
	buttonNames.push_back("F5 Move");
	buttonNames.push_back("F6 New Folder");
	buttonNames.push_back("F7 Delete");
	buttonNames.push_back("Alt+F4 Exit");
	for (int i = 0; i < 6; ++i)
		makeButton(window, buttonNames[i], 214.f * i,view_mode, currentPath, files,event,Selected);
}
