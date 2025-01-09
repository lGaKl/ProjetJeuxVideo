#include "GameView.h"
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
/*
This GameView class is responsible for rendering the visual elements of the game. It manages the game window,
the player's and enemy's cards, health, validations, and card descriptions. It updates the display based on the game's state,
including the characters' health, available cards, and displays text for the player regarding the game's situation.
*/
// Constructor of GameView: initializes the window and graphical assets.
GameView::GameView() : window(sf::VideoMode::getDesktopMode(), "C++ Project", sf::Style::Default) {
    // Load the font used for various UI elements.
    std::random_device rd;  // Random number generator for seeding.
    rng = std::mt19937(rd());  // Initialize the generator with a random seed.

    // Enable vertical synchronization for smoother rendering.
    window.setVerticalSyncEnabled(true);

    // Attempt to load the font file.
    if (!font.loadFromFile("Font/retro-land-mayhem.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Load the background texture and apply it to a sprite.
    if (!backgroundTexture.loadFromFile("Image/fond.png")) {
        std::cerr << "Error loading the background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background image to fit the window size.
    float scaleXBackground = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleYBackground = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleXBackground, scaleYBackground);

    // Load the player's texture (image file).
    if (!playerTexture.loadFromFile("Image/player.png")) {
        std::cerr << "Error loading the player texture!" << std::endl;
    }

    // Obtain the original dimensions of the player texture.
    sf::Vector2u textureSize = playerTexture.getSize();

    // Calculate the desired dimensions for scaling the player texture.
    float targetWidth = 130.0f;
    float targetHeight = static_cast<float>(targetWidth) / textureSize.x * textureSize.y;

    // Compute the scale factors for resizing the texture.
    float scaleXPlayer = targetWidth / textureSize.x;
    float scaleYPlayer = targetHeight / textureSize.y;

    // Set the player texture to the sprite and apply scaling.
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(330.0f, 220.0f);  // Set the player's position on the screen.
    playerSprite.setScale(scaleXPlayer, scaleYPlayer);  // Scale the player texture.

    // Randomly select and load the enemy texture.
    std::string enemyImage = chooseEnemyImage();
    if (!enemyTexture.loadFromFile(enemyImage)) {
        std::cerr << "Error loading the enemy texture!" << std::endl;
    }
    enemySprite.setTexture(enemyTexture);
    enemySprite.setPosition(1370.0f, 220.0f);  // Set the enemy's position.
    enemySprite.setScale(0.9f, 1.0f);  // Scale as needed.

    // Configure the text displaying information about the card being played.
    cardPlayedText.setFont(font);
    cardPlayedText.setCharacterSize(20);
    cardPlayedText.setFillColor(sf::Color::White);
    cardPlayedText.setPosition(550.f, 620.f);

    // Initialize the validation circle (used for gameplay interactions).
    initValidationCircle();

    // Configure the situation rectangle (for messages or status updates).
    situation.setSize(sf::Vector2f(1200.f, 50.f));
    situation.setFillColor(sf::Color::Blue);
    situation.setOutlineColor(sf::Color::Black);
    situation.setOutlineThickness(2.f);
    situation.setPosition(400.f, 600.f);

    // Configure the player's name and health text displays.
    playerNameText.setFont(font);
    playerNameText.setCharacterSize(40);
    playerNameText.setFillColor(sf::Color::Green);
    playerNameText.setString("Player");
    playerNameText.setPosition(330.0f, 150.0f);

    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(30);
    playerHealthText.setFillColor(sf::Color::Green);
    playerHealthText.setPosition(330.0f, 370.0f);

    // Configure the enemy's name and health text displays.
    enemyNameText.setFont(font);
    enemyNameText.setCharacterSize(40);
    enemyNameText.setFillColor(sf::Color::Red);
    enemyNameText.setString("Enemy");
    enemyNameText.setPosition(1370.0f, 150.0f);

    enemyHealthText.setFont(font);
    enemyHealthText.setCharacterSize(30);
    enemyHealthText.setFillColor(sf::Color::Red);
    enemyHealthText.setPosition(1370.0f, 370.0f);

    // Load and configure the victory screen texture.
    if (!victoryTexture.loadFromFile("Image/Crocofest_sexy.png")) {
        std::cerr << "Error loading the victory image!" << std::endl;
    }
    victorySprite.setTexture(victoryTexture);
    victorySprite.setScale(
        static_cast<float>(window.getSize().x) / victoryTexture.getSize().x,
        static_cast<float>(window.getSize().y) / victoryTexture.getSize().y
    );

    // Load and configure the defeat screen texture.
    if (!defeatTexture.loadFromFile("Image/GoldoCPC_GameOver2.png")) {
        std::cerr << "Error loading the defeat image!" << std::endl;
    }
    defeatSprite.setTexture(defeatTexture);
    defeatSprite.setScale(
        static_cast<float>(window.getSize().x) / defeatTexture.getSize().x,
        static_cast<float>(window.getSize().y) / defeatTexture.getSize().y
    );

    // Load and configure the "Back to menu" button and text.
    if (!backArrowTexture.loadFromFile("Image/backArrow.png")) {
        std::cerr << "Error loading the 'backArrow' image!" << std::endl;
    }
    backArrowSprite.setTexture(backArrowTexture);
    backArrowSprite.setPosition(20.0f, 20.0f);  // Position the back arrow in the top-left corner.
    backArrowSprite.setScale(1.5f, 1.5f);  // Scale the back arrow image.

    // Configure the text for the "Back to menu" button.
    backArrowText.setFont(font);
    backArrowText.setString("Back to menu");
    backArrowText.setCharacterSize(22);
    backArrowText.setFillColor(sf::Color::Black);

    // Center the "Back to menu" text within the back arrow sprite.
    sf::FloatRect textBounds = backArrowText.getLocalBounds();
    sf::FloatRect arrowBounds = backArrowSprite.getGlobalBounds();
    backArrowText.setPosition(
        arrowBounds.left + (arrowBounds.width - textBounds.width) / 2,
        arrowBounds.top + (arrowBounds.height - textBounds.height) / 2 - 10
    );
}

// Returns a reference to the validation circle, allowing external access to modify or query its properties.
sf::CircleShape& GameView::getValidationCircle() {
    return validationCircle;
}
/*
// Randomly selects an enemy image from a predefined list of image file paths.
std::string GameView::chooseEnemyImage() {
    // Define a list of possible enemy image paths.
    std::vector<std::string> enemyImages = {"Image/enemy1.png", "Image/enemy2.png", "Image/enemy3.png", "Image/enemy4.png", "Image/enemy5.png"};

    // Create a uniform distribution to randomly select an index.
    std::uniform_int_distribution<int> dist(0, enemyImages.size() - 1);

    // Generate a random index using the RNG.
    int index = dist(rng);

    // Return the file path of the randomly chosen image.
    return enemyImages[index];
}
*/



std::string GameView::chooseEnemyImage() {
    // Initialize the random number generator with a seed based on the system clock
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed); // Random number generator with the seed

    // Generate a random number between 1 and 4
    std::uniform_int_distribution<int> dist(1, 5); // Uniform distribution between 1 and 4
    int randomNumber = dist(rng); // Generate the random number

    // Display the generated random number in the console
    std::cout << "Random number generated: " << randomNumber << std::endl;

    // Construct the image path corresponding to the random number
    std::string imagePath = "Image/Enemy" + std::to_string(randomNumber) + ".png";

    // Return the image path
    return imagePath;
}


// Updates the text display for both the player's and enemy's health.
void GameView::updateHealthDisplay(int playerHealth, int enemyHealth) {
    // Set the player's health display text.
    playerHealthText.setString("Health: " + std::to_string(playerHealth));

    // Set the enemy's health display text.
    enemyHealthText.setString("Health: " + std::to_string(enemyHealth));
}

bool isHovered = false; // Variable to track whether the validation circle is being hovered.

// Initializes the validation circle and its associated text.
void GameView::initValidationCircle() {
    // Set up the circle's properties (radius, color, outline, position).
    validationCircle.setRadius(50.0f);
    validationCircle.setFillColor(sf::Color::Red);
    validationCircle.setOutlineColor(sf::Color::Black);
    validationCircle.setOutlineThickness(3.0f);
    validationCircle.setPosition(1600.0f, 700.0f); // Initial position on the screen.

    // Set up the text to be displayed inside the circle.
    validationCircleText.setFont(font);
    validationCircleText.setString("Play");
    validationCircleText.setCharacterSize(22);
    validationCircleText.setFillColor(sf::Color::White);

    // Get the bounds of the text and the circle to calculate centering.
    sf::FloatRect textBounds = validationCircleText.getLocalBounds();
    sf::FloatRect circleBounds = validationCircle.getGlobalBounds();

    // Center the text within the circle.
    validationCircleText.setPosition(
        circleBounds.left + (circleBounds.width - textBounds.width) / 2 - textBounds.left,
        circleBounds.top + (circleBounds.height - textBounds.height) / 2 - textBounds.top
    );
}

// Updates the hover state of the validation circle based on the mouse position.
void GameView::updateValidationCircleHover(const sf::Vector2i& mousePosition) {
    // Get the bounds of the validation circle.
    sf::FloatRect circleBounds = validationCircle.getGlobalBounds();

    // Check if the mouse is hovering over the circle.
    if (circleBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (!isHovered) {
            // Change the circle's appearance when hovered.
            validationCircle.setFillColor(sf::Color::Blue); // Hover color: Blue
            validationCircleText.setFillColor(sf::Color::Yellow); // Text color: Yellow
            isHovered = true;
        }
    } else {
        if (isHovered) {
            // Revert the circle's appearance to the default state.
            validationCircle.setFillColor(sf::Color::Red); // Default color: Red
            validationCircleText.setFillColor(sf::Color::White); // Default text color: White
            isHovered = false;
        }
    }
}

// Renders the game view, including all elements such as the background, player, enemy, cards, and UI elements.
void GameView::render(const Player& player, const std::vector<Card>& cards, int selectedCardIndex, const Enemy& enemy) {
    window.clear();

    // Draw the background image.
    window.draw(backgroundSprite);

    // Draw the player and their associated elements (sprite, name, health).
    window.draw(playerSprite);
    window.draw(playerNameText);
    window.draw(playerHealthText);

    // Draw the enemy and their associated elements (sprite, name, health).
    window.draw(enemySprite);
    window.draw(enemyNameText);
    window.draw(enemyHealthText);

    // Draw the "Back to Menu" button and its text.
    window.draw(backArrowSprite);
    window.draw(backArrowText);

    // Update and display the player's and enemy's health values.
    updateHealthDisplay(player.getHealth(), enemy.getHealth());

    // Draw the validation circle and its text.
    window.draw(validationCircle);
    window.draw(validationCircleText);

    // Render the player's cards and highlight the selected card.
    renderCards(cards, selectedCardIndex);

    // Draw the situation rectangle and the text describing the card played or game status.
    window.draw(situation);
    window.draw(cardPlayedText);

    // Display the final rendered frame on the screen.
    window.display();
}

// Splits a text string into multiple lines to fit within a specified maximum width.
std::vector<std::string> wrapText(const std::string& text, const sf::Font& font, float maxWidth, unsigned int fontSize) {
    std::vector<std::string> lines;
    std::string currentLine;
    std::istringstream stream(text);
    std::string word;

    // Process each word in the text.
    while (stream >> word) {
        // Test if adding the word exceeds the maximum width.
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        sf::Text testText(testLine, font, fontSize);

        // If the line exceeds the maximum width, start a new line.
        if (testText.getLocalBounds().width > maxWidth) {
            if (!currentLine.empty()) {
                lines.push_back(currentLine);
            }
            currentLine = word;  // Start a new line with the current word.
        } else {
            currentLine = testLine;  // Add the word to the current line.
        }
    }

    // Add the last line to the list.
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}

// Renders the cards on the screen and highlights the selected card.
void GameView::renderCards(const std::vector<Card>& cards, int selectedCardIndex) {
    float xPos = 500.0f;  // Initial X position for the cards.
    float yPos = 700.0f;  // Initial Y position for the cards.
    float cardWidth = 230.0f;  // Card width.
    float cardHeight = 270.0f;  // Card height.
    float padding = 20.0f;  // Spacing between cards.

    // Display a maximum of 4 cards.
    size_t numCardsToDisplay = std::min(cards.size(), size_t(4));

    for (size_t i = 0; i < numCardsToDisplay; ++i) {
        const auto& card = cards[i];

        // Set the background color of the card based on its type.
        sf::Color cardColor;
        if (card.getType() == "Att") {
            cardColor = sf::Color(255, 105, 97);  // Red for attack cards.
        } else if (card.getType() == "HP") {    // Green for heal cards.
            cardColor = sf::Color(0, 239, 129);
        } else if (card.getType() == "Def") {     // Blue for def cards.
            cardColor = sf::Color(119, 181, 254);
        } else if (card.getType() == "Bonus") {   // orange for bonus cards.
            cardColor = sf::Color(255, 174, 59);
        } else {
            cardColor = sf::Color(50, 50, 150);  // Default color for unknown types.
        }

        // Create a rectangle to represent the card.
        sf::RectangleShape cardRect(sf::Vector2f(cardWidth, cardHeight));

        // Check if the card is selected and adjust its appearance.
        if (selectedCardIndex == static_cast<int>(i)) {
            cardRect.setOutlineColor(sf::Color::Yellow);  // Yellow outline for selected card.
            cardRect.setOutlineThickness(4);  // Thicker outline for selected card.
            cardRect.setFillColor(cardColor + sf::Color(50, 50, 50));  // Brightened color.
        } else {
            cardRect.setOutlineColor(sf::Color::White);  // White outline for non-selected cards.
            cardRect.setOutlineThickness(2);  // Normal outline thickness.
            cardRect.setFillColor(cardColor);  // Default color.
        }

        cardRect.setPosition(xPos, yPos);  // Set the card's position.

        // Draw the card rectangle.
        window.draw(cardRect);

        // Draw the card's name and value at the top of the rectangle.
        sf::Text cardName;
        cardName.setFont(font);  // Set the font for the name.
        cardName.setString(card.getName());
        cardName.setCharacterSize(13);  // Small font size for the name.
        cardName.setFillColor(sf::Color::White);
        cardName.setPosition(xPos + 10.0f, yPos + 10.0f);  // Position the name within the rectangle.

        sf::Text cardValue;
        cardValue.setFont(font);  // Set the font for the value.
        cardValue.setString(card.getValue());
        cardValue.setCharacterSize(15);  // Slightly larger font for the value.
        cardValue.setFillColor(sf::Color::White);
        cardValue.setPosition(xPos + cardWidth - 60.0f, yPos + 10.0f);  // Position the value within the rectangle.

        // Draw the card's name and value.
        window.draw(cardName);
        window.draw(cardValue);

        // Draw the card's image if it has a valid texture.
        if (card.getTexture().getSize().x != 0 && card.getTexture().getSize().y != 0) {
            sf::Sprite cardSprite;
            cardSprite.setTexture(card.getTexture());  // Set the card's texture.
            // Scale the sprite to fit within the rectangle.
            float spriteHeight = cardHeight - 40.0f;  // Leave space for name and value.
            cardSprite.setScale(cardWidth / card.getTexture().getSize().x, spriteHeight / card.getTexture().getSize().y);
            cardSprite.setPosition(xPos, yPos + 30.0f);  // Position the sprite below the name and value.

            // Draw the card's image.
            window.draw(cardSprite);
        }

        // Move the X position for the next card.
        xPos += cardWidth + padding;
    }
}

// Updates the text describing the card that was played.
void GameView::updateCardPlayedText(const Card& card) {
    cardPlayedText.setString("Card Played: " + card.getName());
}

// Updates the situation text to reflect the game's current state.
void GameView::updateSituationText(const std::string& situationText) {
    cardPlayedText.setString(situationText);
}

// Checks whether the game window is currently open.
bool GameView::isWindowOpen() const {
    return window.isOpen();
}

// Displays the victory screen with the victory sprite.
void GameView::displayVictoryScreen() {
    window.clear();
    window.draw(victorySprite);
    window.display();
}

// Displays the defeat screen with the defeat sprite.
void GameView::displayDefeatScreen() {
    window.clear();
    window.draw(defeatSprite);
    window.display();
}

// Getter for player sprite
sf::Sprite& GameView::getPlayerSprite() {
    return playerSprite;
}

// Getter for enemy sprite
sf::Sprite& GameView::getEnemySprite() {
    return enemySprite;
}

// Getter for player health text
sf::Text& GameView::getPlayerHealthText() {
    return playerHealthText;
}

// Getter for enemy health text
sf::Text& GameView::getEnemyHealthText() {
    return enemyHealthText;
}


// Getter for card played text
sf::Text& GameView::getCardPlayedText() {
    return cardPlayedText;
}

// Getter for situation rectangle
sf::RectangleShape& GameView::getSituation() {
    return situation;
}

// Getter for back arrow sprite
sf::Sprite& GameView::getBackArrowSprite() {
    return backArrowSprite;
}

// Getter for back arrow text
sf::Text& GameView::getBackArrowText() {
    return backArrowText;
}

// Getter for victory sprite
sf::Sprite& GameView::getVictorySprite() {
    return victorySprite;
}

// Getter for defeat sprite
sf::Sprite& GameView::getDefeatSprite() {
    return defeatSprite;
}

sf::Texture& GameView::getEnemyTexture() {
    return enemyTexture;
}

// Getter for font (if needed for text customization)
sf::Font& GameView::getFont() {
    return font;
}
