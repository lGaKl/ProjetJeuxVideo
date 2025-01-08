#include "MenuView.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

MenuView::MenuView(sf::RenderWindow& window) : window(window), isHovered(false) {
    window.create(sf::VideoMode::getDesktopMode(), "Menu", sf::Style::Default);
    // Charger l'image de fond
    if (!backgroundTexture.loadFromFile("Image/GoldoCPC_Title_Overscan.png")) {
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

    // Configurer le rectangle du bouton
    startButtonRect.setSize(sf::Vector2f(750.f, 150.f));
    startButtonRect.setFillColor(sf::Color(0, 0, 255)); // Couleur initiale
    startButtonRect.setOutlineColor(sf::Color::White); // Bordure
    startButtonRect.setOutlineThickness(4.f);
    startButtonRect.setPosition(
        (window.getSize().x - startButtonRect.getSize().x) / 2,
        (window.getSize().y - startButtonRect.getSize().y) / 2
    );

    // Configurer le texte du bouton
    startButtonText.setFont(font);
    startButtonText.setString("Start Game");
    startButtonText.setCharacterSize(80);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(
        startButtonRect.getPosition().x + (startButtonRect.getSize().x - startButtonText.getLocalBounds().width) / 2,
        startButtonRect.getPosition().y + (startButtonRect.getSize().y - startButtonText.getLocalBounds().height) / 2 - 10
    );
}

void MenuView::updateHoverState(const sf::Vector2i& mousePosition) {
    sf::FloatRect buttonBounds = startButtonRect.getGlobalBounds();
    if (buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        if (!isHovered) {
            // Change le style pour un effet "hover"
            startButtonRect.setFillColor(sf::Color(255, 0, 0)); // Couleur plus claire
            startButtonRect.setOutlineColor(sf::Color::Yellow); // Changer la bordure
            startButtonText.setFillColor(sf::Color::Yellow); // Changer la couleur du texte
            isHovered = true;
        }
    } else {
        if (isHovered) {
            // Revenir au style par défaut
            startButtonRect.setFillColor(sf::Color(0, 0, 255)); // Couleur initiale
            startButtonRect.setOutlineColor(sf::Color::White);
            startButtonText.setFillColor(sf::Color::White);
            isHovered = false;
        }
    }
}

void MenuView::render() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(startButtonRect);
    window.draw(startButtonText);
    window.display();
}

bool MenuView::isStartButtonClicked(const sf::Vector2i& mousePosition) {
    sf::FloatRect buttonBounds = startButtonRect.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}
