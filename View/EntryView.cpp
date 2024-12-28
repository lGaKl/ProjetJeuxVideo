#include "EntryView.h"
#include <iostream>

void EntryView::loadBackground(const std::string& filePath) {
    if (!backgroundTexture.loadFromFile(filePath)) {
        std::cerr << "Erreur : Impossible de charger l'image de fond depuis le chemin : " << filePath << std::endl;
        throw std::runtime_error("Impossible de charger l'image de fond !");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Redimensionner l'image pour qu'elle prenne toute la fenêtre
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);
}

void EntryView::render() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite); // Dessine l'image de fond
    window.draw(startButton);      // Dessine le bouton
    window.draw(buttonText);
    window.display();
}

EntryView::EntryView()
    : window(sf::VideoMode::getDesktopMode(), "Projet C++", sf::Style::Default) {
    // Chargez ici les ressources nécessaires comme les textures ou polices
}

void EntryView::setupButton() {
    // Charger la police
    if (!font.loadFromFile("D:/USB/ECOLE/BAC3/C++/Projet_C++/Projet_C++/View/Font/retro-land-mayhem.ttf")) {
        throw std::runtime_error("Impossible de charger la police !");
    }

    // Configurer le bouton
    startButton.setSize(sf::Vector2f(400, 80)); // Taille du bouton
    startButton.setFillColor(sf::Color::Blue);
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOutlineThickness(2);

    // Positionner le bouton au centre
    sf::Vector2u windowSize = window.getSize();
    startButton.setPosition((windowSize.x - startButton.getSize().x) / 2,
                            (windowSize.y - startButton.getSize().y) / 2);

    // Configurer le texte du bouton
    buttonText.setFont(font);
    buttonText.setString("Start Game");
    buttonText.setCharacterSize(50);
    buttonText.setFillColor(sf::Color(255, 215, 0));

    // Centrer le texte sur le bouton
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(startButton.getPosition().x + startButton.getSize().x / 2,
                           startButton.getPosition().y + startButton.getSize().y / 2);
}

bool EntryView::isButtonClicked(const sf::Vector2f& mousePos) {
    sf::FloatRect buttonBounds = startButton.getGlobalBounds();
    return buttonBounds.contains(mousePos);
}

bool EntryView::isButtonHovered(const sf::Vector2f& mousePos) {
    sf::FloatRect buttonBounds = startButton.getGlobalBounds();
    return buttonBounds.contains(mousePos);
}

sf::RectangleShape& EntryView::getButton() {
    return startButton;
}

void EntryView::resizeElements() {
    // Redimensionner le background
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);

    // Repositionner et redimensionner le bouton
    startButton.setPosition((windowSize.x - startButton.getSize().x) / 2,
                            (windowSize.y - startButton.getSize().y) / 2);

    // Centrer le texte sur le bouton après redimensionnement
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(startButton.getPosition().x + startButton.getSize().x / 2,
                           startButton.getPosition().y + startButton.getSize().y / 2);
}


bool EntryView::isWindowOpen() const { return window.isOpen(); }
