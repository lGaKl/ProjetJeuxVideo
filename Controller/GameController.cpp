#include "GameController.h"
#include <SFML/Window.hpp>
#include <iostream>

GameController::GameController() {
    view.loadBackground("D:/USB/ECOLE/BAC3/C++/Projet_C++/Projet_C++/View/Assets/GoldoCPC_Title_Overscan.png");
}

void GameController::run() {
    view.setupButton(); // Configure le bouton

    while (view.isWindowOpen()) {
        sf::Event event;
        while (view.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                view.getWindow().close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                view.getWindow().setView(sf::View(visibleArea));
                view.resizeElements(); // Met à jour la taille des éléments
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(view.getWindow());
                sf::Vector2f worldPos = view.getWindow().mapPixelToCoords(pixelPos);

                if (view.isButtonClicked(worldPos)) {
                    std::cout << "Bouton 'Start Game' cliqué !" << std::endl;
                }
            }
        }

        // Gestion du survol
        sf::Vector2i pixelPos = sf::Mouse::getPosition(view.getWindow());
        sf::Vector2f worldPos = view.getWindow().mapPixelToCoords(pixelPos);

        if (view.isButtonHovered(worldPos)) {
            view.getButton().setFillColor(sf::Color::Red);
        } else {
            view.getButton().setFillColor(sf::Color::Blue);
        }

        view.render();
    }
}
