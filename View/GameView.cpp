#include "GameView.h"
#include <iostream>
#include <sstream>

/*
This GameView class is responsible for rendering the visual elements of the game. It manages the game window,
the player's and enemy's cards, health, validations, and card descriptions. It updates the display based on the game's state,
including the characters' health, available cards, and displays text for the player regarding the game's situation.
*/
// Constructor of GameView: initializes the window and font
GameView::GameView() : window(sf::VideoMode(1900, 1080), "C++ Project") {
    // Loading the font

    window.setVerticalSyncEnabled(true);
    if (!font.loadFromFile("Arial.ttf")) {  // Make sure you have an "arial.ttf" font in the directory or change the path
        std::cerr << "Error loading font!" << std::endl;
    }


    cardPlayedText.setFont(font);
    cardPlayedText.setCharacterSize(20);
    cardPlayedText.setFillColor(sf::Color::White);
    cardPlayedText.setPosition(550.f, 620.f);
    initValidationCircle();
/*
    validationCircle.setRadius(50.0f);
    validationCircle.setFillColor(sf::Color::Green);
    validationCircle.setOutlineColor(sf::Color::White);
    validationCircle.setOutlineThickness(3.0f);
    validationCircle.setPosition(1600.0f, 700.0f);
*/
    situation.setSize(sf::Vector2f(1200.f, 50.f));  // Rectangle size (300x150)
    situation.setFillColor(sf::Color::Red);  // Fill color
    situation.setOutlineColor(sf::Color::White);  // Outline color
    situation.setOutlineThickness(2.f);  // Outline thickness
    situation.setPosition(400.f, 600.f);

    playerRect.setSize(sf::Vector2f(200.0f, 100.0f));
    playerRect.setFillColor(sf::Color::Blue);
    playerRect.setPosition(100.0f, 300.0f);

    playerNameText.setFont(font);
    playerNameText.setCharacterSize(20);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setString("Player");
    playerNameText.setPosition(100.0f, 270.0f);

    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(20);
    playerHealthText.setFillColor(sf::Color::White);
    playerHealthText.setPosition(100.0f, 420.0f);

    enemyRect.setSize(sf::Vector2f(200.0f, 100.0f));
    enemyRect.setFillColor(sf::Color::Red);
    enemyRect.setPosition(1600.0f, 300.0f);
    enemyNameText.setFont(font);
    enemyNameText.setCharacterSize(20);
    enemyNameText.setFillColor(sf::Color::White);
    enemyNameText.setString("Enemy");
    enemyNameText.setPosition(1600.0f, 270.0f);

    enemyHealthText.setFont(font);
    enemyHealthText.setCharacterSize(20);
    enemyHealthText.setFillColor(sf::Color::White);
    enemyHealthText.setPosition(1600.0f, 420.0f);
}

sf::CircleShape& GameView::getValidationCircle() {
    return validationCircle;
}

void GameView::updateHealthDisplay(int playerHealth, int enemyHealth) {
    playerHealthText.setString("Health: " + std::to_string(playerHealth));
    enemyHealthText.setString("Health: " + std::to_string(enemyHealth));
}

void GameView::initValidationCircle() {
    validationCircle.setRadius(50.0f);  // Définir les propriétés du cercle
    validationCircle.setFillColor(sf::Color::Green);
    validationCircle.setOutlineColor(sf::Color::White);
    validationCircle.setOutlineThickness(3.0f);
    validationCircle.setPosition(1600.0f, 700.0f);  // Position initiale
}
void GameView::render(const Player& player, const std::vector<Card>& cards, int selectedCardIndex, const Enemy& enemy) {
    window.clear();

    window.draw(playerRect);
    window.draw(playerNameText);
    window.draw(playerHealthText);
    window.draw(enemyRect);
    window.draw(enemyNameText);
    window.draw(enemyHealthText);
    updateHealthDisplay(player.getHealth(), enemy.getHealth());

    window.draw(validationCircle);
    // Display the cards
    renderCards(cards, selectedCardIndex);


   // window.draw(validationCircle);
    window.draw(situation);
    window.draw(cardPlayedText);
    window.display();  // Show everything on the screen
}

// Function to split a text string into multiple lines based on the maximum width
std::vector<std::string> wrapText(const std::string& text, const sf::Font& font, float maxWidth, unsigned int fontSize) {
    std::vector<std::string> lines;
    std::string currentLine;
    std::istringstream stream(text);
    std::string word;

    // List each word in the text
    while (stream >> word) {
        // Try to add the word to the current line
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        sf::Text testText(testLine, font, fontSize);

        // If the line exceeds the maximum card width, start a new line
        if (testText.getLocalBounds().width > maxWidth) {
            if (!currentLine.empty()) {
                lines.push_back(currentLine);
            }
            currentLine = word;  // Start a new line with the current word
        } else {
            currentLine = testLine;  // Continue adding words to the current line
        }
    }

    // Add the last line
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}

void GameView::renderCards(const std::vector<Card>& cards, int selectedCardIndex) {
    float xPos = 500.0f;  // X position for the cards
    float yPos = 700.0f;  // Y position for the cards (to offset them slightly down)
    float cardWidth = 230.0f;  // Width of the cards
    float cardHeight = 270.0f; // Height of the cards
    float padding = 20.0f;  // Padding between the cards

    // Limit the display to 4 cards
    size_t numCardsToDisplay = std::min(cards.size(), size_t(4));

    for (size_t i = 0; i < numCardsToDisplay; ++i) {
        const auto& card = cards[i];

        // Définir la couleur de fond en fonction du type
        sf::Color cardColor;
        if (card.getType() == "Att") {
            cardColor = sf::Color(255, 0, 0);  // Rouge
        } else if (card.getType() == "Heal") {
            cardColor = sf::Color(255, 182, 193);  // Rose
        } else if (card.getType() == "Def") {
            cardColor = sf::Color(0, 255, 0);  // Vert
        } else if (card.getType() == "Bonus") {
            cardColor = sf::Color(0, 0, 255);  // Bleu
        } else {
            cardColor = sf::Color(50, 50, 150);  // Couleur par défaut
        }

        // Créer un rectangle pour la carte
        sf::RectangleShape cardRect(sf::Vector2f(cardWidth, cardHeight));

        // Vérifier si cette carte est sélectionnée
        if (selectedCardIndex == static_cast<int>(i)) {
            cardRect.setOutlineColor(sf::Color::Yellow);  // Bordure jaune pour la sélection
            cardRect.setOutlineThickness(4);  // Bordure plus épaisse
            cardRect.setFillColor(cardColor + sf::Color(50, 50, 50));  // Rendre la couleur légèrement plus lumineuse
        } else {
            cardRect.setOutlineColor(sf::Color::White);  // Bordure blanche normale
            cardRect.setOutlineThickness(2);  // Bordure normale
            cardRect.setFillColor(cardColor);  // Couleur normale
        }

        cardRect.setPosition(xPos, yPos);  // Positionner le rectangle

        // Dessiner le rectangle de la carte
        window.draw(cardRect);

        // Dessiner le nom et la valeur en haut de la carte
        sf::Text cardName;
        cardName.setFont(font);  // Assurez-vous que la police est chargée
        cardName.setString(card.getName());
        cardName.setCharacterSize(18);  // Taille de la police pour le nom
        cardName.setFillColor(sf::Color::White);  // Couleur du texte
        cardName.setPosition(xPos + 10.0f, yPos + 10.0f);  // Positionner le texte du nom à l'intérieur du rectangle

        sf::Text cardValue;
        cardValue.setFont(font);  // Assurez-vous que la police est chargée
        cardValue.setString(card.getValue());
        cardValue.setCharacterSize(18);  // Taille de la police pour la valeur
        cardValue.setFillColor(sf::Color::White);  // Couleur du texte
        cardValue.setPosition(xPos + cardWidth - 50.0f, yPos + 10.0f);  // Positionner le texte de la valeur à l'intérieur du rectangle

        // Dessiner le nom et la valeur
        window.draw(cardName);
        window.draw(cardValue);

        // Dessiner l'image de la carte (à l'intérieur du rectangle)
        if (!card.getTexture().getSize().x == 0 && !card.getTexture().getSize().y == 0) {
            sf::Sprite cardSprite;
            cardSprite.setTexture(card.getTexture());  // Définir la texture pour le sprite
            // Mettre l'échelle pour s'adapter à la moitié inférieure du rectangle
            float spriteHeight = cardHeight - 40.0f;  // Soustraire l'espace pour le nom/valeur
            cardSprite.setScale(cardWidth / card.getTexture().getSize().x, spriteHeight / card.getTexture().getSize().y);  // Mettre à l'échelle pour s'adapter
            cardSprite.setPosition(xPos, yPos + 30.0f);  // Positionner le sprite sous le nom/valeur

            // Dessiner l'image de la carte
            window.draw(cardSprite);
        }

        // Ajuster la position pour la prochaine carte
        xPos += cardWidth + padding;  // Passer à la position suivante pour la carte suivante
    }
}



void GameView::updateCardPlayedText(const Card& card) {
    cardPlayedText.setString("");
    // Update the text with the card information
    cardPlayedText.setString("Card Played: " + card.getName());
}

void GameView::updateSituationText(const std::string& situationText) {
    cardPlayedText.setString(situationText);
}

// Method to check if the window is open
bool GameView::isWindowOpen() const {

    return window.isOpen();
}


