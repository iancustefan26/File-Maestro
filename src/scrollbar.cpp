#include <SFML/Graphics.hpp>
#include "scrollbar.h"

void renderScroll(sf::RenderWindow& window,sf::Event event){
    

    const int numFiles = 100;
    const float fileHeight = 30.0f;
    const float viewableFiles = window.getSize().y / fileHeight;

    float scrollbarHeight = window.getSize().y;
    float scrollbarWidth = 15.0f;
    float scrollbarPosition = 0.0f;
    float scrollbarSpeed = 20.0f;

    sf::RectangleShape files[numFiles];
    for (int i = 0; i < numFiles; ++i) {
        files[i].setSize(sf::Vector2f(200.0f, fileHeight));
        files[i].setPosition(0.0f, i * fileHeight);
    }

    sf::RectangleShape scrollbar(sf::Vector2f(scrollbarWidth, scrollbarHeight));
    scrollbar.setPosition(window.getSize().x - scrollbarWidth, 0);

    sf::RectangleShape slider(sf::Vector2f(scrollbarWidth, (viewableFiles / numFiles) * scrollbarHeight));
    slider.setFillColor(sf::Color::Blue);

            if (event.type == sf::Event::MouseWheelScrolled) {
                // Handle mouse wheel scrolling
                scrollbarPosition -= event.mouseWheelScroll.delta * scrollbarSpeed;

                // Limit scrollbar position to valid range
                if (scrollbarPosition < 0.0f) {
                    scrollbarPosition = 0.0f;
                }
                else if (scrollbarPosition > numFiles - viewableFiles) {
                    scrollbarPosition = numFiles - viewableFiles;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Handle left mouse button click to directly jump to a position
                float mouseY = static_cast<float>(event.mouseButton.y);
                scrollbarPosition = mouseY / window.getSize().y * (numFiles - viewableFiles);
            }
        

        // Rendering logic
        

        // Draw your files based on the scrollbar position
      

        // Draw the scrollbar background
        window.draw(scrollbar);

        // Calculate and set the slider position
        float sliderPositionY = scrollbar.getPosition().y + (scrollbarPosition / (numFiles - viewableFiles)) * (scrollbarHeight - slider.getSize().y);
        slider.setPosition(scrollbar.getPosition().x, sliderPositionY);

        // Calculate and set the slider size
        float sliderSize = (viewableFiles / numFiles) * scrollbarHeight;
        slider.setSize(sf::Vector2f(scrollbarWidth, sliderSize));

        window.draw(slider);

        
    


}