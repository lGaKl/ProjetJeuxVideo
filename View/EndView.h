#ifndef END_VIEW_H
#define END_VIEW_H

#include <SFML/Graphics.hpp>

// The EndView class represents the screen displayed at the end of the game.
// It includes a background and a "Go to Menu" button.
class EndView {
private:
    sf::RenderWindow& window;             // Reference to the render window
    sf::Texture backgroundTexture;       // Texture for the background image
    sf::Sprite backgroundSprite;         // Sprite to display the background texture
    sf::Font font;                       // Font for button text
    sf::RectangleShape menuButtonRect;   // Rectangle for the "Go to Menu" button
    sf::Text menuButtonText;             // Text displayed on the button
    bool isHovered;                      // Hover state of the button

public:
    // Constructor: Initializes the end view with a background and button
    EndView(sf::RenderWindow& window, const std::string& backgroundImagePath);

    // Renders the end screen
    void render();

    // Checks if the "Go to Menu" button is clicked
    bool isMenuButtonClicked(const sf::Vector2i& mousePosition);

    // Updates the hover state of the button based on the mouse position
    void updateHoverState(const sf::Vector2i& mousePosition);
};

#endif // END_VIEW_H
