#include "GameController.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "Enemy.h"
#include "DeckEnemy.h"

bool isEnemyTurnReady = false;
bool canInteractWithCards = true;
bool isArchorActive = false;
bool isVenusiaActive = false;
Enemy enemy(100);
bool isPlayerTurn = true;  // Indique si c'est le tour du joueur
bool hasValidated = false;
GameController::GameController() : selectedCardIndex(-1), player(100) {
    // Cartes de soin (PV)

    deck.addCard(Card("Soin Basique", "Restaure 10 points de vie à Goldorak.", "PV", "10"));
    deck.addCard(Card("Réparation Mineure", "Restaure 15 points de vie à Goldorak.", "PV", "15"));
    deck.addCard(Card("Restauration Complète", "Restaure 20 points de vie à Goldorak.", "PV", "20"));

    deck.addCard(Card("Soin Basique", "Restaure 10 points de vie à Goldorak.", "PV", "10"));
    deck.addCard(Card("Réparation Mineure", "Restaure 15 points de vie à Goldorak.", "PV", "15"));
    deck.addCard(Card("Restauration Complète", "Restaure 20 points de vie à Goldorak.", "PV", "20"));


    // Cartes d'attaque (Att)
    deck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    deck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    deck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));

    deck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    deck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    deck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));

    deck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    deck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    deck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));

    deck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    deck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    deck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));
    // Cartes de défense (Def)
    deck.addCard(Card("Bouclier Léger", "Bloque 10 points de dégâts.", "Def", "10"));
    deck.addCard(Card("Bouclier Renforcé", "Bloque 15 points de dégâts.", "Def", "15"));
    deck.addCard(Card("Barrière Énergétique", "Bloque 20 points de dégâts.", "Def", "20"));

    deck.addCard(Card("Bouclier Léger", "Bloque 10 points de dégâts.", "Def", "10"));
    deck.addCard(Card("Bouclier Renforcé", "Bloque 15 points de dégâts.", "Def", "15"));
    deck.addCard(Card("Barrière Énergétique", "Bloque 20 points de dégâts.", "Def", "20"));



    // Cartes de bonus
    deck.addCard(Card("Boost d'Alcor", "Rejouer directement et vos dégats seront doublés", "Bonus", "Dégâts * 2"));
    deck.addCard(Card("Soutien de Venusia", "Double les PV restaurés par Goldorak pendant 1 tour.", "Bonus", "Heal * 2"));

    deck.addCard(Card("Protection d'Actarus", "Double la défense de Goldorak pendant 1 tour.", "Bonus", "Def * 2"));
    deck.addCard(Card("Repioche Stratégique", "Permet de repiocher une carte immédiatement.", "Bonus", "Repioche"));
    deck.addCard(Card("Repioche Stratégique", "Permet de repiocher une carte immédiatement.", "Bonus", "Repioche"));
    deck.addCard(Card("Repioche Stratégique", "Permet de repiocher une carte immédiatement.", "Bonus", "Repioche"));
    deck.addCard(Card("Repioche Stratégique", "Permet de repiocher une carte immédiatement.", "Bonus", "Repioche"));
    deck.addCard(Card("Repioche Stratégique", "Permet de repiocher une carte immédiatement.", "Bonus", "Repioche"));

    enemyDeck.addCard(Card("Soin Basique", "Restaure 10 points de vie à Goldorak.", "PV", "10"));
    enemyDeck.addCard(Card("Réparation Mineure", "Restaure 15 points de vie à Goldorak.", "PV", "15"));
    enemyDeck.addCard(Card("Restauration Complète", "Restaure 20 points de vie à Goldorak.", "PV", "20"));

    enemyDeck.addCard(Card("Soin Basique", "Restaure 10 points de vie à Goldorak.", "PV", "10"));
    enemyDeck.addCard(Card("Réparation Mineure", "Restaure 15 points de vie à Goldorak.", "PV", "15"));
    enemyDeck.addCard(Card("Restauration Complète", "Restaure 20 points de vie à Goldorak.", "PV", "20"));



    enemyDeck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    enemyDeck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    enemyDeck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));

    enemyDeck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    enemyDeck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    enemyDeck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));

    enemyDeck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    enemyDeck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    enemyDeck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));

    enemyDeck.addCard(Card("Laser Basique", "Inflige 10 points de dégâts à l'ennemi.", "Att", "15"));
    enemyDeck.addCard(Card("Laser Amélioré", "Inflige 15 points de dégâts à l'ennemi.", "Att", "20"));
    enemyDeck.addCard(Card("Tir Puissant", "Inflige 20 points de dégâts à l'ennemi.", "Att", "25"));


    enemyDeck.addCard(Card("Bouclier Léger", "Bloque 10 points de dégâts.", "Def", "10"));
    enemyDeck.addCard(Card("Bouclier Renforcé", "Bloque 15 points de dégâts.", "Def", "15"));
    enemyDeck.addCard(Card("Barrière Énergétique", "Bloque 20 points de dégâts.", "Def", "20"));

    enemyDeck.addCard(Card("Bouclier Léger", "Bloque 10 points de dégâts.", "Def", "10"));
    enemyDeck.addCard(Card("Bouclier Renforcé", "Bloque 15 points de dégâts.", "Def", "15"));
    enemyDeck.addCard(Card("Barrière Énergétique", "Bloque 20 points de dégâts.", "Def", "20"));




    enemyDeck.shuffle();
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

    for (size_t i = 0; i < drawnCards.size(); ++i) {
        std::cout << "Carte " << (i + 1) << ": " << drawnCards[i].getName() << " - " << drawnCards[i].getDescription() << std::endl;
    }


    while (view.isWindowOpen()) {
        handleEvents();//Gére interaction utilisateur et evenement de la fenétre
        update(); // met a jour l'état du jeu (joueur,carte etc)
        render(); // Gére l'affichage visuel des élement du jeu
    }
}

void GameController::handleCardClick(const sf::Vector2i& mousePos) {
    float xPos = 500.0f;  // Position X initiale pour les cartes
    float yPos = 700.0f;  // Position Y initiale pour les cartes
    float cardWidth = 200.0f;  // Largeur des cartes
    float cardHeight = 250.0f; // Hauteur des cartes
    float padding = 20.0f;  // Espacement entre les cartes

    // Parcourez les cartes affichées
    for (size_t i = 0; i < drawnCards.size(); ++i) {
        // Calculer la zone de la carte
        sf::FloatRect cardBounds(xPos, yPos, cardWidth, cardHeight);

        // Vérifiez si la position de la souris est dans les limites de cette carte
        if (cardBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedCardIndex = static_cast<int>(i); // Mettre à jour la carte sélectionnée

            // Mettre à jour le texte de la situation en fonction de la carte jouée
            if (drawnCards[selectedCardIndex].getType() == "Att") {
                int damage = std::stoi(drawnCards[selectedCardIndex].getValue());
                if (isArchorActive) {
                    damage *= 2;  // Double les dégâts
                }
                std::string situationText = "Vous attaquez l'ennemi avec " + drawnCards[selectedCardIndex].getName() + " infligeant " + std::to_string(damage) + " dégâts.";
                view.updateSituationText(situationText);  // Mise à jour du texte dans la situation
            } else if (drawnCards[selectedCardIndex].getType() == "PV") {
                int healing = std::stoi(drawnCards[selectedCardIndex].getValue());
                 if (isVenusiaActive) {
                    healing *= 2;  // Double les dégâts
                }
                std::string situationText = "Vous vous soignez avec " + drawnCards[selectedCardIndex].getName() + " et restaurez " + std::to_string(healing) + " points de vie.";
                view.updateSituationText(situationText);  // Mise à jour du texte dans la situation
            } else if (drawnCards[selectedCardIndex].getType() == "Def") {
                int defenseValue = std::stoi(drawnCards[selectedCardIndex].getValue());


                std::string situationText = "Vous vous défendez avec " + drawnCards[selectedCardIndex].getName() +
                                ", bloquant jusqu'à " + std::to_string(defenseValue) + " dégâts pendant ce tour.";
                view.updateSituationText(situationText);  // Mise à jour du texte dans la situation
            } else if (drawnCards[selectedCardIndex].getType() == "Bonus") {
                std::string situationText = "Vous activez un bonus avec " + drawnCards[selectedCardIndex].getName();
                view.updateSituationText(situationText);  // Mise à jour du texte dans la situation
            } else if (drawnCards[selectedCardIndex].getType() == "Bonus") {
                std::string situationText = "Vous activez un bonus avec " + drawnCards[selectedCardIndex].getName();
                view.updateSituationText(situationText);  // Mise à jour du texte dans la situation
            }

            return; // On arrête ici, car une carte a été sélectionnée
        }

        // Mettre à jour xPos pour la carte suivante
        xPos += cardWidth + padding;
    }

    // Si aucun clic sur une carte, réinitialiser la sélection
    selectedCardIndex = -1;
    std::cout << "Aucune carte sélectionnée." << std::endl;
}


void GameController::handleEvents() {
    sf::Event event;
    while (view.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            view.getWindow().close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(view.getWindow());
                sf::Vector2f circlePosition = view.getValidationCircle().getPosition();
                float radius = view.getValidationCircle().getRadius();

                // Clic sur le cercle de validation
                if (std::pow(mousePosition.x - (circlePosition.x + radius), 2) +
                    std::pow(mousePosition.y - (circlePosition.y + radius), 2) <=
                    std::pow(radius, 2)) {

                    if (isEnemyTurnReady) {
                        // L'ennemi joue son tour
                        enemyTurn();
                        isEnemyTurnReady = false; // Réinitialisation pour le prochain tour
                        canInteractWithCards = true; // Réactiver les interactions après le tour de l'ennemi
                    } else {
                        // Le joueur termine son tour
                        if (selectedCardIndex >= 0 && selectedCardIndex < static_cast<int>(drawnCards.size())) {
                            playPlayerTurn();
                            if(isArchorActive==false && isVenusiaActive==false){
                                    isEnemyTurnReady = true;
                                    view.updateSituationText("Tour de l'ennemi. Cliquez pour continuer.");
                                    canInteractWithCards = false;
                            }

                            //canInteractWithCards=true;

                            // Désactiver les interactions pendant le message
                        } else {
                            std::cout << "Aucune carte sélectionnée." << std::endl;
                        }
                    }
                } else if (canInteractWithCards) {
                    // Clic sur une carte (autorisé uniquement si les interactions sont activées)
                    handleCardClick(mousePosition);
                }
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (canInteractWithCards) { // Autoriser les raccourcis uniquement si les interactions sont activées
                if (event.key.code == sf::Keyboard::Left) {
                    selectedCardIndex = std::max(0, selectedCardIndex - 1);
                } else if (event.key.code == sf::Keyboard::Right) {
                    selectedCardIndex = std::min(static_cast<int>(drawnCards.size() - 1), selectedCardIndex + 1);
                }
            }
        }
    }
}




void GameController::playPlayerTurn() {
    if (drawnCards[selectedCardIndex].getType() == "Att") {
        int damage = std::stoi(drawnCards[selectedCardIndex].getValue());
        if (isArchorActive) {
            damage *= 2;
            isArchorActive = false;  // Désactiver le boost après l'attaque
        }
        enemy.takeDamage(damage);
        std::cout << "Vous attaquez l'ennemi avec " << drawnCards[selectedCardIndex].getName()
                  << ", infligeant " << damage << " dégâts." << std::endl;

    } else if (drawnCards[selectedCardIndex].getType() == "PV") {
        int healing = std::stoi(drawnCards[selectedCardIndex].getValue());
        if (isVenusiaActive) {
            healing *= 2;
            isVenusiaActive = false;  // Désactiver le boost après l'attaque
        }
        player.heal(healing);
        enemy.takeDamage(0);
        std::cout << "Vous vous soignez avec " << drawnCards[selectedCardIndex].getName()
                  << ", récupérant " << healing << " PV." << std::endl;
    }else if (drawnCards[selectedCardIndex].getType() == "Def") {
    int defenseValue = std::stoi(drawnCards[selectedCardIndex].getValue());
    player.applyDefense(defenseValue);
    enemy.takeDamage(0);
    std::cout << "Vous vous défendez avec " << drawnCards[selectedCardIndex].getName()
              << ", bloquant jusqu'à " << defenseValue << " dégâts." << std::endl;
    } else if (drawnCards[selectedCardIndex].getType() == "Bonus" && drawnCards[selectedCardIndex].getName() == "Boost d'Alcor") {
        // Si la carte "Boost d'Alcor" est activée
        std::cout << "Vous activez Boost d'Alcor. Vous pouvez continuer à jouer." << std::endl;
        isArchorActive = true; // Activer l'effet de boost pour le prochain tour
        // Garder le tour du joueur actif
        view.updateHealthDisplay(player.getHealth(), enemy.getHealth());
        drawnCards.erase(drawnCards.begin() + selectedCardIndex);
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());
        }
        selectedCardIndex = -1;
        return; // Sortir de la méthode pour ne pas passer au tour de l'ennemi
    }else if (drawnCards[selectedCardIndex].getType() == "Bonus" && drawnCards[selectedCardIndex].getName() == "Soutien de Venusia") {
        // Si la carte "Boost d'Alcor" est activée
        std::cout << "Vous activez Soutien de Venusia. Vous pouvez continuer à jouer." << std::endl;
        isVenusiaActive = true; // Activer l'effet de boost pour le prochain tour
        // Garder le tour du joueur actif
        view.updateHealthDisplay(player.getHealth(), enemy.getHealth());
        drawnCards.erase(drawnCards.begin() + selectedCardIndex);
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());
        }
        selectedCardIndex = -1;
        return; // Sortir de la méthode pour ne pas passer au tour de l'ennemi
    }


    // Mise à jour de l'état du jeu
    view.updateHealthDisplay(player.getHealth(), enemy.getHealth());

    // Supprimer la carte utilisée et repiocher
    drawnCards.erase(drawnCards.begin() + selectedCardIndex);
    if (!deck.isEmpty()) {
        drawnCards.push_back(deck.drawCard());
    }

    // Réinitialiser la sélection
    selectedCardIndex = -1;
}



void GameController::enemyTurn() {
    if (!enemyDeck.isEmpty()) {
        Card enemyCard = enemyDeck.drawCard();
        std::string enemyActionText;

        if (enemyCard.getType() == "Att") {
            int damage = std::stoi(enemyCard.getValue());
            player.takeDamage(damage);
            enemyActionText = "L'ennemi attaque avec " + enemyCard.getName() +
                              ", infligeant " + std::to_string(damage) + " dégâts.";
            std::cout << enemyActionText << std::endl;
        } else if (enemyCard.getType() == "PV") {
            int healing = std::stoi(enemyCard.getValue());
            enemy.heal(healing);
            player.takeDamage(0);
            enemyActionText = "L'ennemi se soigne avec " + enemyCard.getName() +
                              ", récupérant " + std::to_string(healing) + " PV.";
            std::cout << enemyActionText << std::endl;
        }else if (enemyCard.getType() == "Def") {
            int defenseValue = std::stoi(enemyCard.getValue());
            enemy.applyDefense(defenseValue);
            player.takeDamage(0);
            enemyActionText = "L'ennemi se défend avec " + enemyCard.getName() +
                      ", bloquant jusqu'à " + std::to_string(defenseValue) + " dégâts.";
            std::cout << enemyActionText << std::endl;
        }

        // Mise à jour de l'état du jeu et de l'affichage
        view.updateHealthDisplay(player.getHealth(), enemy.getHealth());
        view.updateSituationText(enemyActionText); // Afficher ce que l'ennemi a fait
    }
}







void GameController::update() {
    if (enemy.getHealth() <= 0) {
        std::cout << "L'ennemi a été vaincu !" << std::endl;
        // Terminer le jeu ou afficher un message
    }
    if (player.getHealth() <= 0) {
        std::cout << "Vous avez été vaincu !" << std::endl;
        // Vous pouvez ajouter des actions supplémentaires pour finir le jeu ici
    }

}

void GameController::render() {
    // Réinitialisez la fenêtre avant de la redessiner (effacer l'écran)
    view.getWindow().clear();

    // Afficher les informations du joueur (exemple : afficher la santé)
    view.render(player,drawnCards,selectedCardIndex,enemy);


    view.renderCards(drawnCards, selectedCardIndex);


    // Afficher les éléments sur la fenêtre
    view.getWindow().display();
}

