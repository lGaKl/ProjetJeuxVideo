#include "EndView.h"
#include <iostream>

EndView::EndView(sf::RenderWindow& window, const std::string& backgroundImagePath) : window(window), isHovered(false) {
    window.create(sf::VideoMode::getDesktopMode(), "End Screen", sf::Style::Default);
    // Charger l'image de fond
    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        std::cerr << "Erreur : Impossible de charger l'image de fond !\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Ajuster l'image de fond à la taille de la fenêtre
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Charger la police
    if (!font.loadFromFile("retro-land-mayhem.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !\n";
    }

    // Configurer le bouton "Go to Menu"
    menuButtonRect.setSize(sf::Vector2f(400.f, 100.f));
    menuButtonRect.setFillColor(sf::Color(0, 0, 255)); // Couleur initiale
    menuButtonRect.setOutlineColor(sf::Color::White); // Bordure
    menuButtonRect.setOutlineThickness(4.f);
    menuButtonRect.setPosition(
        window.getSize().x - menuButtonRect.getSize().x - 50.f, // 50px de marge à droite
        window.getSize().y - menuButtonRect.getSize().y - 50.f  // 50px de marge en bas
    );

    // Configurer le texte du bouton
    menuButtonText.setFont(font);
    menuButtonText.setString("Go to Menu");
    menuButtonText.setCharacterSize(40);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(
        menuButtonRect.getPosition().x + (menuButtonRect.getSize().x - menuButtonText.getLocalBounds().width) / 2,
        menuButtonRect.getPosition().y + (menuButtonRect.getSize().y - menuButtonText.getLocalBounds().height) / 2 - 10
    );
}

void EndView::updateHoverState(const sf::Vector2i& mousePosition) {
    sf::FloatRect buttonBounds = menuButtonRect.getGlobalBounds();
    if (buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (!isHovered) {
            menuButtonRect.setFillColor(sf::Color(255, 0, 0)); // Couleur sur survol
            menuButtonRect.setOutlineColor(sf::Color::Yellow);
            menuButtonText.setFillColor(sf::Color::Yellow);
            isHovered = true;
        }
    } else {
        if (isHovered) {
            menuButtonRect.setFillColor(sf::Color(0, 0, 255)); // Couleur par défaut
            menuButtonRect.setOutlineColor(sf::Color::White);
            menuButtonText.setFillColor(sf::Color::White);
            isHovered = false;
        }
    }
}

bool EndView::isMenuButtonClicked(const sf::Vector2i& mousePosition) {
    sf::FloatRect buttonBounds = menuButtonRect.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

void EndView::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(menuButtonRect);
    window.draw(menuButtonText);
    window.display();
}
