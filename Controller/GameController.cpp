#include "GameController.h"
#include <SFML/Window.hpp>
#include <iostream>





GameController::GameController() : player(100) {
    // Ajout de cartes au deck pour le test
    deck.addCard(Card("Attaque Laser", "Un laser puissant qui inflige 20 points de dégâts à l'ennemi.", "Attaque", "20"));
    deck.addCard(Card("Bouclier Energétique", "Un bouclier qui bloque 15 points de dégâts.", "Défense", "15"));
    deck.addCard(Card("Soin d'Urgence", "Restaure 30 points de vie au joueur.", "Soin", "30"));
    deck.addCard(Card("Double Attaque", "Permet de lancer deux attaques successives.", "Attaque", "10"));
    deck.addCard(Card("Réacteur Plasma", "Augmente la puissance d'attaque de 50% pendant 3 tours.", "Amélioration", "50%"));
    deck.addCard(Card("Explosion", "Inflige 40 points de dégâts à tous les ennemis à l'écran.", "Attaque", "40"));
    deck.addCard(Card("Téléportation", "Permet au joueur de se déplacer instantanément sur n'importe quelle case de la carte.", "Objet", "N/A"));
    deck.addCard(Card("Soutien Alcor", "Alcor envoie une assistance qui réduit les dégâts subis de 10 pour 5 tours.", "Soin", "10"));
    deck.addCard(Card("Coup Critique", "Inflige un coup critique qui fait le double de dégâts.", "Attaque", "50"));
    deck.addCard(Card("Guérison Rapide", "Soigne 10 points de vie à chaque tour pendant 3 tours.", "Soin", "10 par tour"));
}

// Méthode run(boucle principale du jeu)
void GameController::run() {
    deck.shuffle();
    drawnCards.clear();
   std::cout << "Début de la boucle de tirage de cartes" << std::endl;
    for (int i = 0; i < 4; ++i) {
    if (!deck.isEmpty()) {
        Card drawnCard = deck.drawCard();
        drawnCards.push_back(drawnCard);
    }
    }

    for (int i = 0; i < drawnCards.size(); ++i) {
        std::cout << "Carte " << (i + 1) << ": " << drawnCards[i].getName() << " - " << drawnCards[i].getDescription() << std::endl;
    }


    while (view.isWindowOpen()) {
        handleEvents();//Gére interaction utilisateur et evenement de la fenétre
        update(); // met a jour l'état du jeu (joueur,carte etc)
        render(); // Gére l'affichage visuel des élement du jeu
    }
}

// Gère les événements SFML liés à la fenêtre et aux entrées clavier
void GameController::handleEvents() {
    sf::Event event;
    while (view.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            view.getWindow().close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                player.takeDamage(5); // Exemple : perte de points de vie
            }
        }
    }
}

void GameController::update() {
    if (!deck.isEmpty()) {
        player.takeDamage(1); // Exemple simple
    }
}

void GameController::render() {
    // Réinitialisez la fenêtre avant de la redessiner (effacer l'écran)
    view.getWindow().clear();

    // Afficher les informations du joueur (exemple : afficher la santé)
    view.render(player,drawnCards);

    view.renderCards(drawnCards);

    // Afficher les éléments sur la fenêtre
    view.getWindow().display();
}

