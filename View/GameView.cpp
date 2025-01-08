#include "GameView.h"
#include <iostream>
#include <sstream>
#include <random>

/*
This GameView class is responsible for rendering the visual elements of the game. It manages the game window,
the player's and enemy's cards, health, validations, and card descriptions. It updates the display based on the game's state,
including the characters' health, available cards, and displays text for the player regarding the game's situation.
*/
// Constructor of GameView: initializes the window and font
GameView::GameView() : window(sf::VideoMode::getDesktopMode(), "C++ Project", sf::Style::Default) {
    // Loading the font

    std::random_device rd;  // Générateur de nombres aléatoires basé sur une source externe
    rng = std::mt19937(rd());  // Initialise le générateur avec un "seed" aléatoire

    window.setVerticalSyncEnabled(true);
    if (!font.loadFromFile("retro-land-mayhem.ttf")) {  // Make sure you have an "arial.ttf" font in the directory or change the path
        std::cerr << "Error loading font!" << std::endl;
    }

    // Charger la texture pour le fond d'écran
    if (!backgroundTexture.loadFromFile("Image/fond.png")) {
        std::cerr << "Erreur de chargement de la texture du fond!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Ajuster l'échelle si la taille de l'image ne correspond pas à la taille de la fenêtre
    float scaleXBackground = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleYBackground = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleXBackground, scaleYBackground);

    // Charger la texture
    if (!playerTexture.loadFromFile("Image/player.png")) {  // Remplacez "player.png" par le chemin de votre fichier
        std::cerr << "Erreur de chargement de la texture du joueur!" << std::endl;
    }

    // Obtenez les dimensions de la texture originale
    sf::Vector2u textureSize = playerTexture.getSize();

    // Dimensions souhaitées (par exemple, largeur de 100 pixels)
    float targetWidth = 100.0f;
    float targetHeight = static_cast<float>(targetWidth) / textureSize.x * textureSize.y;

    // Appliquez le facteur de mise à l'échelle pour le joueur
    float scaleXPlayer = targetWidth / textureSize.x;
    float scaleYPlayer = targetHeight / textureSize.y;

    // Appliquer la texture au sprite et ajuster la taille
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(330.0f, 220.0f);  // Position similaire au rectangle initial
    playerSprite.setScale(scaleXPlayer, scaleYPlayer);  // Mise à l'échelle pour ajuster la taille

    // Choisir aléatoirement l'image de l'ennemi
    std::string enemyImage = chooseEnemyImage();
    if (!enemyTexture.loadFromFile(enemyImage)) {  // Utilisez l'image choisie aléatoirement
        std::cerr << "Erreur de chargement de la texture de l'ennemi!" << std::endl;
    }
    enemySprite.setTexture(enemyTexture);
    enemySprite.setPosition(1370.0f, 220.0f);  // Position similaire au rectangle initial
    enemySprite.setScale(1.0f, 1.0f);  // Ajustez la taille si nécessaire

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
    situation.setFillColor(sf::Color::Blue);  // Fill color
    situation.setOutlineColor(sf::Color::Black);  // Outline color
    situation.setOutlineThickness(2.f);  // Outline thickness
    situation.setPosition(400.f, 600.f);


    playerNameText.setFont(font);
    playerNameText.setCharacterSize(40);
    playerNameText.setFillColor(sf::Color::Green);
    playerNameText.setString("Player");
    playerNameText.setPosition(330.0f, 150.0f);

    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(30);
    playerHealthText.setFillColor(sf::Color::Green);
    playerHealthText.setPosition(330.0f, 370.0f);

    /*enemyRect.setSize(sf::Vector2f(200.0f, 100.0f));
    enemyRect.setFillColor(sf::Color::Red);
    enemyRect.setPosition(1600.0f, 300.0f);*/
    enemyNameText.setFont(font);
    enemyNameText.setCharacterSize(40);
    enemyNameText.setFillColor(sf::Color::Red);
    enemyNameText.setString("Enemy");
    enemyNameText.setPosition(1370.0f, 150.0f);

    enemyHealthText.setFont(font);
    enemyHealthText.setCharacterSize(30);
    enemyHealthText.setFillColor(sf::Color::Red);
    enemyHealthText.setPosition(1370.0f, 370.0f);

    if(!victoryTexture.loadFromFile("Image/Crocofest_sexy.png")){
        std::cerr << "Erreur de chargement de l'image de victoire!" << std::endl;
    }
    victorySprite.setTexture(victoryTexture);
    victorySprite.setScale(
        static_cast<float>(window.getSize().x) / victoryTexture.getSize().x,
        static_cast<float>(window.getSize().y) / victoryTexture.getSize().y
    );

    if (!defeatTexture.loadFromFile("Image/GoldoCPC_GameOver2.png")) {
        std::cerr << "Erreur de chargement de l'image de défaite!" << std::endl;
    }
    defeatSprite.setTexture(defeatTexture);
    defeatSprite.setScale(
        static_cast<float>(window.getSize().x) / defeatTexture.getSize().x,
        static_cast<float>(window.getSize().y) / defeatTexture.getSize().y
    );

    if (!backArrowTexture.loadFromFile("Image/backArrow.png")) {
        std::cerr << "Erreur de chargement de l'image 'backArrow' !" << std::endl;
    }

    backArrowSprite.setTexture(backArrowTexture);
    backArrowSprite.setPosition(20.0f, 20.0f); // Position en haut à gauche
    backArrowSprite.setScale(1.5f, 1.5f); // Ajustez l'échelle si nécessaire

    // Configurer le texte "Back to menu"
    backArrowText.setFont(font);
    backArrowText.setString("Back to menu");
    backArrowText.setCharacterSize(22);
    backArrowText.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = backArrowText.getLocalBounds();

    // Centrer le texte dans le sprite de la flèche
    sf::FloatRect arrowBounds = backArrowSprite.getGlobalBounds();
    backArrowText.setPosition(
        arrowBounds.left + (arrowBounds.width - textBounds.width) / 2,
        arrowBounds.top + (arrowBounds.height - textBounds.height) / 2 - 10
    );
}

sf::CircleShape& GameView::getValidationCircle() {
    return validationCircle;
}

std::string GameView::chooseEnemyImage() {
    // Définir une liste d'images possibles pour l'ennemi
    std::vector<std::string> enemyImages = {"Image/enemy1.png", "Image/enemy2.png", "Image/enemy3.png", "Image/enemy4.png", "Image/enemy5.png"};

    // Distribution uniforme entre 0 et le nombre d'images
    std::uniform_int_distribution<int> dist(0, enemyImages.size() - 1);

    // Choisir une image aléatoire
    int index = dist(rng);

    // Retourner le chemin de l'image choisie
    return enemyImages[index];
}

void GameView::updateHealthDisplay(int playerHealth, int enemyHealth) {
    playerHealthText.setString("Health: " + std::to_string(playerHealth));
    enemyHealthText.setString("Health: " + std::to_string(enemyHealth));
}

bool isHovered = false; // Variable pour gérer l'état de survol
void GameView::initValidationCircle() {
    // Initialiser le cercle
    validationCircle.setRadius(50.0f);  // Définir les propriétés du cercle
    validationCircle.setFillColor(sf::Color::Red);
    validationCircle.setOutlineColor(sf::Color::Black);
    validationCircle.setOutlineThickness(3.0f);
    validationCircle.setPosition(1600.0f, 700.0f);  // Position initiale

    // Initialiser le texte
    validationCircleText.setFont(font);
    validationCircleText.setString("Play");
    validationCircleText.setCharacterSize(22);
    validationCircleText.setFillColor(sf::Color::White);

    // Obtenir les dimensions du texte et du cercle
    sf::FloatRect textBounds = validationCircleText.getLocalBounds();
    sf::FloatRect circleBounds = validationCircle.getGlobalBounds();

    // Centrer le texte dans le cercle
    validationCircleText.setPosition(
        circleBounds.left + (circleBounds.width - textBounds.width) / 2 - textBounds.left,
        circleBounds.top + (circleBounds.height - textBounds.height) / 2 - textBounds.top
    );
}

void GameView::updateValidationCircleHover(const sf::Vector2i& mousePosition) {
    sf::FloatRect circleBounds = validationCircle.getGlobalBounds();

    if (circleBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (!isHovered) {
            validationCircle.setFillColor(sf::Color::Blue); // Couleur de survol : Bleu
            validationCircleText.setFillColor(sf::Color::Yellow); // Texte en Jaune
            isHovered = true;
        }
    } else {
        if (isHovered) {
            validationCircle.setFillColor(sf::Color::Red); // Couleur par défaut : Rouge
            validationCircleText.setFillColor(sf::Color::White); // Texte en Blanc
            isHovered = false;
        }
    }
}

void GameView::render(const Player& player, const std::vector<Card>& cards, int selectedCardIndex, const Enemy& enemy) {
    window.clear();

    // Dessiner le fond d'écran
    window.draw(backgroundSprite);

    // Dessiner les autres éléments par-dessus
    window.draw(playerSprite);
    window.draw(playerNameText);
    window.draw(playerHealthText);
    window.draw(enemySprite);
    window.draw(enemyNameText);
    window.draw(enemyHealthText);

    // Dessiner la flèche de retour
    window.draw(backArrowSprite);
    window.draw(backArrowText);

    updateHealthDisplay(player.getHealth(), enemy.getHealth());

    window.draw(validationCircle);
    window.draw(validationCircleText);
    renderCards(cards, selectedCardIndex);

    window.draw(situation);
    window.draw(cardPlayedText);

    window.display();
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
        cardName.setCharacterSize(13);  // Taille de la police pour le nom
        cardName.setFillColor(sf::Color::White);  // Couleur du texte
        cardName.setPosition(xPos + 10.0f, yPos + 10.0f);  // Positionner le texte du nom à l'intérieur du rectangle

        sf::Text cardValue;
        cardValue.setFont(font);  // Assurez-vous que la police est chargée
        cardValue.setString(card.getValue());
        cardValue.setCharacterSize(15);  // Taille de la police pour la valeur
        cardValue.setFillColor(sf::Color::White);  // Couleur du texte
        cardValue.setPosition(xPos + cardWidth - 60.0f, yPos + 10.0f);  // Positionner le texte de la valeur à l'intérieur du rectangle

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

void GameView::displayVictoryScreen() {
    window.clear();
    window.draw(victorySprite);
    window.display();
}

void GameView::displayDefeatScreen() {
    window.clear();
    window.draw(defeatSprite);
    window.display();
}
