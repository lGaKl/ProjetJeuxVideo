#include "GameView.h"
#include <iostream>
#include <sstream>

// Constructeur de GameView : initialisation de la fenêtre et de la police
GameView::GameView() : window(sf::VideoMode(1900, 1080), "Projet C++") {
    // Chargement de la police
    if (!font.loadFromFile("bin/Arial.ttf")) {  // Assurez-vous d'avoir une police "arial.ttf" dans le répertoire ou modifiez le chemin
        std::cerr << "Erreur de chargement de la police!" << std::endl;
    }
}

void GameView::render(const Player& player, const std::vector<Card>& cards) {
    window.clear();  // Effacer la fenêtre avant de redessiner

    // Mettre à jour et afficher la santé du joueur
    playerHealthText.setString("Santé: " + std::to_string(player.getHealth()));
    window.draw(playerHealthText);

    // Afficher les cartes
    renderCards(cards);

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

void GameView::renderCards(const std::vector<Card>& cards) {
    float xPos = 50.0f;  // Position X pour les cartes
    float yPos = 150.0f;  // Position Y pour les cartes (pour les décaler un peu vers le bas)
    float cardWidth = 300.0f;  // Largeur des cartes
    float cardHeight = 150.0f; // Hauteur des cartes
    float padding = 20.0f;  // Espacement entre les cartes
    unsigned int fontSize = 14;  // Taille de la police pour la description

    // Limiter l'affichage à 4 cartes
    size_t numCardsToDisplay = std::min(cards.size(), size_t(4));

    for (size_t i = 0; i < numCardsToDisplay; ++i) {
        const auto& card = cards[i];

        // Créer un rectangle pour la carte
        sf::RectangleShape cardRect(sf::Vector2f(cardWidth, cardHeight));
        cardRect.setFillColor(sf::Color(50, 50, 150));  // Couleur de fond de la carte
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

// Méthode pour vérifier si la fenêtre est ouverte
bool GameView::isWindowOpen() const {
    return window.isOpen();
}
