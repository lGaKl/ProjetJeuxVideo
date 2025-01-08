#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Deck.h"
#include "Enemy.h"
#include <random>

// The GameView class is responsible for rendering the game's graphical interface.
// It manages the display of the player, enemy, cards, and various UI elements.
class GameView {
private:
    // Selects a random enemy image from a predefined list.
    std::string chooseEnemyImage();

    sf::RenderWindow window;             // The main game window.
    sf::Font font;                       // Font used for text elements.
    sf::Text cardPlayedText;             // Text displaying the card that was played.
    sf::Text validationCircleText;       // Text displayed inside the validation circle.
    sf::CircleShape validationCircle;    // Circle used for user validation interactions.
    sf::RectangleShape situation;        // Rectangle used to display game status or messages.

    // Player-related UI components.
    sf::Text playerNameText;             // Text displaying the player's name.
    sf::Text playerHealthText;           // Text displaying the player's health.
    sf::Texture playerTexture;           // Texture for the player's sprite.
    sf::Sprite playerSprite;             // Sprite representing the player.

    // Enemy-related UI components.
    sf::Text enemyNameText;              // Text displaying the enemy's name.
    sf::Text enemyHealthText;            // Text displaying the enemy's health.
    sf::Texture enemyTexture;            // Texture for the enemy's sprite.
    sf::Sprite enemySprite;              // Sprite representing the enemy.

    // Background and end screen assets.
    sf::Texture backgroundTexture;       // Texture for the background image.
    sf::Sprite backgroundSprite;         // Sprite for the background image.
    sf::Texture victoryTexture;          // Texture for the victory screen.
    sf::Sprite victorySprite;            // Sprite for the victory screen.
    sf::Texture defeatTexture;           // Texture for the defeat screen.
    sf::Sprite defeatSprite;             // Sprite for the defeat screen.

    // "Back to Menu" button components.
    sf::Texture backArrowTexture;        // Texture for the "Back to Menu" button arrow.
    sf::Sprite backArrowSprite;          // Sprite for the "Back to Menu" button arrow.
    sf::Text backArrowText;              // Text for the "Back to Menu" button.

    // Random number generator for enemy image selection.
    std::mt19937 rng;

public:
    // Constructor: Initializes the game view and loads necessary assets.
    GameView();

    // Returns a reference to the main game window.
    sf::RenderWindow& getWindow() { return window; }

    // Renders the game elements, including the player, enemy, cards, and UI.
    void render(const Player& player, const std::vector<Card>& cards, int selectedCardIndex, const Enemy& enemy);

    // Renders the player's cards on the screen.
    void renderCards(const std::vector<Card>& cards, int selectedCardIndex);

    // Checks if the game window is currently open.
    bool isWindowOpen() const;

    // Updates the text displaying the card that was played.
    void updateCardPlayedText(const Card& card);

    // Updates the health display for both the player and the enemy.
    void updateHealthDisplay(int playerHealth, int enemyHealth);

    // Returns a reference to the validation circle.
    sf::CircleShape& getValidationCircle();

    // Updates the situation text to reflect the current game state.
    void updateSituationText(const std::string& situationText);

    // Initializes the validation circle's properties.
    void initValidationCircle();

    // Displays the victory screen.
    void displayVictoryScreen();

    // Displays the defeat screen.
    void displayDefeatScreen();

    // Gets the bounding rectangle of the "Back to Menu" button.
    sf::FloatRect getBackArrowBounds() const { return backArrowSprite.getGlobalBounds(); }

    // Updates the hover state of the validation circle based on mouse position.
    void updateValidationCircleHover(const sf::Vector2i& mousePosition);
};

#endif // GAMEVIEW_H
