#include "GameView.h"
#include <iostream>
#include <sstream>


// Constructeur de GameView : initialisation de la fenêtre et de la police
GameView::GameView() : window(sf::VideoMode(1900, 1080), "Projet C++") {
    // Chargement de la police

    window.setVerticalSyncEnabled(true);
    if (!font.loadFromFile("bin/Arial.ttf")) {  // Assurez-vous d'avoir une police "arial.ttf" dans le répertoire ou modifiez le chemin
        std::cerr << "Erreur de chargement de la police!" << std::endl;
    }

    cardPlayedText.setFont(font);
    cardPlayedText.setCharacterSize(20);
    cardPlayedText.setFillColor(sf::Color::White);
    cardPlayedText.setPosition(550.f, 620.f);

    validationCircle.setRadius(50.0f);
    validationCircle.setFillColor(sf::Color::Green);
    validationCircle.setOutlineColor(sf::Color::White);
    validationCircle.setOutlineThickness(3.0f);
    validationCircle.setPosition(1600.0f, 700.0f);

    situation.setSize(sf::Vector2f(1200.f, 50.f));  // Taille du rectangle (300x150)
    situation.setFillColor(sf::Color::Red);  // Couleur de remplissage
    situation.setOutlineColor(sf::Color::White);  // Couleur de bordure
    situation.setOutlineThickness(2.f);  // Épaisseur de la bordure
    situation.setPosition(400.f, 600.f);

    playerRect.setSize(sf::Vector2f(200.0f, 100.0f));
    playerRect.setFillColor(sf::Color::Blue);
    playerRect.setPosition(100.0f, 300.0f);

    playerNameText.setFont(font);
    playerNameText.setCharacterSize(20);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setString("Joueur");
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
    enemyNameText.setString("Ennemi");
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
    playerHealthText.setString("Vie : " + std::to_string(playerHealth));
    enemyHealthText.setString("Vie : " + std::to_string(enemyHealth));
}
void GameView::render(const Player& player, const std::vector<Card>& cards,int selectedCardIndex,const Enemy& enemy) {
    window.clear();  // Effacer la fenêtre avant de redessiner

    window.draw(playerRect);
    window.draw(playerNameText);
    window.draw(playerHealthText);
    window.draw(enemyRect);
    window.draw(enemyNameText);
    window.draw(enemyHealthText);
    updateHealthDisplay(player.getHealth(), enemy.getHealth());

    // Afficher les cartes
    renderCards(cards,selectedCardIndex);


    window.draw(validationCircle);
    window.draw(situation);
    window.draw(cardPlayedText);
    window.display();  // Afficher tout à l'écran
}

// Fonction pour diviser une chaîne de texte en plusieurs lignes, en fonction de la largeur maximale
std::vector<std::string> wrapText(const std::string& text, const sf::Font& font, float maxWidth, unsigned int fontSize) {
    std::vector<std::string> lines;
    std::string currentLine;
    std::istringstream stream(text);
    std::string word;

    // Lister chaque mot du texte
    while (stream >> word) {
        // Essayer d'ajouter le mot à la ligne en cours
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        sf::Text testText(testLine, font, fontSize);

        // Si la ligne dépasse la largeur maximale de la carte, commencer une nouvelle ligne
        if (testText.getLocalBounds().width > maxWidth) {
            if (!currentLine.empty()) {
                lines.push_back(currentLine);
            }
            currentLine = word;  // Démarrer une nouvelle ligne avec le mot courant
        } else {
            currentLine = testLine;  // Continuer à ajouter des mots à la ligne actuelle
        }
    }

    // Ajouter la dernière ligne
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}

void GameView::renderCards(const std::vector<Card>& cards,int selectedCardIndex) {
    float xPos = 500.0f;  // Position X pour les cartes
    float yPos = 700.0f;  // Position Y pour les cartes (pour les décaler un peu vers le bas)
    float cardWidth = 200.0f;  // Largeur des cartes
    float cardHeight = 250.0f; // Hauteur des cartes
    float padding = 20.0f;  // Espacement entre les cartes
    unsigned int fontSize = 14;  // Taille de la police pour la description

    // Limiter l'affichage à 4 cartes
    size_t numCardsToDisplay = std::min(cards.size(), size_t(4));

    for (size_t i = 0; i < numCardsToDisplay; ++i) {
        const auto& card = cards[i];

        // Créer un rectangle pour la carte
        sf::RectangleShape cardRect(sf::Vector2f(cardWidth, cardHeight));
         if (selectedCardIndex == static_cast<int>(i)) {
        cardRect.setFillColor(sf::Color(100, 100, 250));  // Couleur surbrillante
        } else {
        cardRect.setFillColor(sf::Color(50, 50, 150));  // Couleur normale
        }
        //cardRect.setFillColor(sf::Color(50, 50, 150));  // Couleur de fond de la carte
        cardRect.setOutlineColor(sf::Color::White);  // Couleur de bordure
        cardRect.setOutlineThickness(2);  // Épaisseur de la bordure
        cardRect.setPosition(xPos, yPos);  // Positionner le rectangle

        // Afficher le rectangle de la carte
        window.draw(cardRect);

        // Créer un objet sf::Text pour afficher le nom de la carte
        sf::Text cardName;
        cardName.setFont(font);  // Assurez-vous que la police est chargée
        cardName.setString(card.getName());
        cardName.setCharacterSize(18);  // Taille du texte pour le nom
        cardName.setFillColor(sf::Color::White);  // Couleur du texte
        cardName.setPosition(xPos + 10.0f, yPos + 10.0f);  // Positionner le texte à l'intérieur du rectangle

        // Afficher le texte du nom de la carte
        window.draw(cardName);

        // Diviser la description en plusieurs lignes si nécessaire
        std::vector<std::string> wrappedDescription = wrapText(card.getDescription(), font, cardWidth - 20.0f, fontSize);

        // Afficher chaque ligne de la description
        float descriptionYPos = yPos + 40.0f;  // Début de la description juste sous le nom
        for (const auto& line : wrappedDescription) {
            sf::Text cardDesc;
            cardDesc.setFont(font);  // Assurez-vous que la police est chargée
            cardDesc.setString(line);
            cardDesc.setCharacterSize(fontSize);  // Taille du texte pour la description
            cardDesc.setFillColor(sf::Color::White);  // Couleur du texte
            cardDesc.setPosition(xPos + 10.0f, descriptionYPos);  // Positionner chaque ligne à l'intérieur du rectangle

            // Afficher le texte de la description
            window.draw(cardDesc);

            // Déplacer vers le bas pour la prochaine ligne
            descriptionYPos += fontSize + 2.0f;  // Ajouter un petit espacement entre les lignes
        }

        // Modifier la position pour la prochaine carte
        xPos += cardWidth + padding;  // Déplacer vers le bas pour la carte suivante
    }
}
void GameView::updateCardPlayedText(const Card& card) {
    cardPlayedText.setString("");
    // Mettre à jour le texte avec les informations de la carte
    cardPlayedText.setString("Carte Jouée: " + card.getName() );

}

void GameView::updateSituationText(const std::string& situationText) {
    cardPlayedText.setString(situationText);
}






// Méthode pour vérifier si la fenêtre est ouverte
bool GameView::isWindowOpen() const {
    return window.isOpen();
}
