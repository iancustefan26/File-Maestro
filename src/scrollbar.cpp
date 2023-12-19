#include <SFML/Graphics.hpp>
#include "scrollbar.h"
void create_scrollbar(sf::RenderWindow& window)
{
    float scrollbarWidth = 20.0f;
    float scrollbarHeight = 400.0f;
    float scrollbarPosX = window.getSize().x - scrollbarWidth;
    float scrollbarPosY = 0.0f;
    float thumbHeight = 50.0f;  // Height of the movable thumb
    float thumbPosY = 0.0f;     // Current position of the thumb

    sf::RectangleShape scrollbar(sf::Vector2f(scrollbarWidth, scrollbarHeight));
    scrollbar.setPosition(scrollbarPosX, scrollbarPosY);
    scrollbar.setFillColor(sf::Color(128, 128, 128)); // Gray color for the scrollbar

    sf::RectangleShape thumb(sf::Vector2f(scrollbarWidth, thumbHeight));
    thumb.setPosition(scrollbarPosX, thumbPosY);
    thumb.setFillColor(sf::Color(192, 192, 192)); // Light gray color for the thumb

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle mouse events for dragging the thumb
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (sf::Mouse::getPosition(window).x >= scrollbarPosX &&
                    sf::Mouse::getPosition(window).x <= scrollbarPosX + scrollbarWidth &&
                    sf::Mouse::getPosition(window).y >= thumbPosY &&
                    sf::Mouse::getPosition(window).y <= thumbPosY + thumbHeight) {
                    // Thumb is clicked, start dragging
                    bool dragging = true;

                    while (dragging) {
                        sf::Event dragEvent;
                        while (window.pollEvent(dragEvent)) {
                            if (dragEvent.type == sf::Event::MouseButtonReleased && dragEvent.mouseButton.button == sf::Mouse::Left) {
                                dragging = false;
                            }

                            if (dragEvent.type == sf::Event::MouseMoved) {
                                // Update thumb position based on mouse movement
                                thumbPosY = std::min(std::max(0.0f, static_cast<float>(sf::Mouse::getPosition(window).y)), scrollbarHeight - thumbHeight);
                                thumb.setPosition(scrollbarPosX, thumbPosY);
                                // Adjust your content based on the thumb position
                                // ...
                            }
                        }

                       
                        window.draw(scrollbar);
                        window.draw(thumb);
                       // window.display();
                    }
                }
            }
        }

        
        window.draw(scrollbar);
        window.draw(thumb);
      // window.display();
    }
}