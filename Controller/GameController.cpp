#include "GameController.h"
#include <SFML/Window.hpp>

GameController::GameController() : player(100) {
    // Ajout de cartes au deck pour le test
    deck.addCard(Card("Carte 1", "Description 1", "Type 1"));
    deck.addCard(Card("Carte 2", "Description 2", "Type 2"));
}

void GameController::run() {
    while (view.isWindowOpen()) {
        // Gestion des événements SFML
        sf::Event event;
        while (view.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                view.getWindow().close();
            }
        }

        // Exemple de mise à jour du joueur
        if (!deck.isEmpty()) {
            player.takeDamage(1);
        }

        // Affichage
        view.render(player);
    }
}
