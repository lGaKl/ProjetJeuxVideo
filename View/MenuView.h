#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "GameView.h"
#include "Player.h"
#include "Deck.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

// The MenuView class represents the main menu of the game.
// It provides methods to render the menu, handle hover interactions, and detect button clicks.
class MenuView {
private:
    sf::RenderWindow& window;               // Reference to the game window where the menu will be displayed.
    sf::Texture backgroundTexture;          // Texture for the menu's background image.
    sf::Sprite backgroundSprite;            // Sprite to display the background texture.
    sf::Font font;                          // Font used for menu text.
    sf::Text startButtonText;               // Text displayed on the "Start Game" button.
    sf::RectangleShape startButtonRect;     // Rectangle representing the "Start Game" button.
    bool isHovered;                         // Boolean to track whether the mouse is hovering over the button.

public:
    // Constructor: Initializes the menu view and sets up its graphical elements.
    MenuView(sf::RenderWindow& window);

    // Renders the menu on the screen, including the background and the "Start Game" button.
    void render();

    // Checks if the "Start Game" button was clicked based on the mouse position.
    bool isStartButtonClicked(const sf::Vector2i& mousePosition);

    // Updates the hover state of the "Start Game" button to provide visual feedback.
    void updateHoverState(const sf::Vector2i& mousePosition);
};

#endif // MENU_VIEW_H
