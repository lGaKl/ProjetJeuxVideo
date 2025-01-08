#include "GameController.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "Enemy.h"
#include "DeckEnemy.h"
#include "windows.h"
#include "mmsystem.h"
#include <SFML/Audio.hpp>
#include "CardFactory.h"
bool isEnemyTurnReady = false;
bool canInteractWithCards = true;
bool isArchorActive = false;
bool isVenusiaActive = false;
Enemy enemy(100);
bool isPlayerTurn = true;  // turnPlayer?
bool hasValidated = false;
GameController::GameController() : selectedCardIndex(-1), player(100) {
//Player's deck
// Heal cards
deck.addCard(CardFactory::createHealCard("Makeshift Repair", "Restores 10 health points to Goldorak.", "HP", "10","Image/Old.png"));
deck.addCard(CardFactory::createHealCard("Actarus Repair", "Restores 15 health points to Goldorak.", "HP", "15","Image/Actarus.png"));
deck.addCard(CardFactory::createHealCard("Pr. Procyon Repair", "Restores 20 health points to Goldorak.", "HP", "20","Image/prof.png"));

deck.addCard(CardFactory::createHealCard("Makeshift Repair", "Restores 10 health points to Goldorak.", "HP", "10","Image/Old.png"));
deck.addCard(CardFactory::createHealCard("Actarus Repair", "Restores 15 health points to Goldorak.", "HP", "15","Image/Actarus.png"));
deck.addCard(CardFactory::createHealCard("Pr. Procyon Repair", "Restores 20 health points to Goldorak.", "HP", "20","Image/prof.png"));

// Attack cards (Att)
deck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
deck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
deck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

deck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
deck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
deck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

deck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
deck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
deck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

deck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
deck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
deck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

// Defense cards (Def)
deck.addCard(CardFactory::createDefenseCard("Light Barrier", "Blocks 10 damage points.", "Def", "10","Image/shield1.png"));
deck.addCard(CardFactory::createDefenseCard("Energy Shield ", "Blocks 15 damage points.", "Def", "15","Image/shield2.png"));
deck.addCard(CardFactory::createDefenseCard("Aegis Véga ", "Blocks 20 damage points.", "Def", "20","Image/shield3.png"));

deck.addCard(CardFactory::createDefenseCard("Light Barrier", "Blocks 10 damage points.", "Def", "10","Image/shield1.png"));
deck.addCard(CardFactory::createDefenseCard("Energy Shield ", "Blocks 15 damage points.", "Def", "15","Image/shield2.png"));
deck.addCard(CardFactory::createDefenseCard("Aegis Véga ", "Blocks 20 damage points.", "Def", "20","Image/shield3.png"));

// Bonus cards
deck.addCard(CardFactory::createBonusCard("Alcor's Boost", "Play again immediately, and your damage will be doubled.", "Bonus", "Dmg*2","Image/alcor.png"));
deck.addCard(CardFactory::createBonusCard("Venusia's Support", "Doubles health restored by Goldorak for 1 turn.", "Bonus", "Hp*2","Image/venusia.png"));

// Enemy's deck

enemyDeck.addCard(CardFactory::createHealCard("Makeshift Repair", "Restores 10 health points to Goldorak.", "HP", "10","Image/Old.png"));
enemyDeck.addCard(CardFactory::createHealCard("Actarus Repair", "Restores 15 health points to Goldorak.", "HP", "15","Image/Actarus.png"));
enemyDeck.addCard(CardFactory::createHealCard("Pr. Procyon Repair", "Restores 20 health points to Goldorak.", "HP", "20","Image/prof.png"));

enemyDeck.addCard(CardFactory::createHealCard("Makeshift Repair", "Restores 10 health points to Goldorak.", "HP", "10","Image/Old.png"));
enemyDeck.addCard(CardFactory::createHealCard("Actarus Repair", "Restores 15 health points to Goldorak.", "HP", "15","Image/Actarus.png"));
enemyDeck.addCard(CardFactory::createHealCard("Pr. Procyon Repair", "Restores 20 health points to Goldorak.", "HP", "20","Image/prof.png"));

// Attack cards (Att)
enemyDeck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

enemyDeck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

enemyDeck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

enemyDeck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15","Image/Cornofulgure.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20","Image/Fulguropoing.png"));
enemyDeck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25","Image/Asterohache.png"));

// Defense cards (Def)
enemyDeck.addCard(CardFactory::createDefenseCard("Light Barrier", "Blocks 10 damage points.", "Def", "10","Image/shield1.png"));
enemyDeck.addCard(CardFactory::createDefenseCard("Energy Shield ", "Blocks 15 damage points.", "Def", "15","Image/shield2.png"));
enemyDeck.addCard(CardFactory::createDefenseCard("Aegis Véga ", "Blocks 20 damage points.", "Def", "20","Image/shield3.png"));

enemyDeck.addCard(CardFactory::createDefenseCard("Light Barrier", "Blocks 10 damage points.", "Def", "10","Image/shield1.png"));
enemyDeck.addCard(CardFactory::createDefenseCard("Energy Shield ", "Blocks 15 damage points.", "Def", "15","Image/shield2.png"));
enemyDeck.addCard(CardFactory::createDefenseCard("Aegis Véga ", "Blocks 20 damage points.", "Def", "20","Image/shield3.png"));


enemyDeck.shuffle();
}


/*void GameController::run() {
    //shuffle the player's cards
    deck.shuffle();
    drawnCards.clear();

    std::cout << "Starting the card drawing loop" << std::endl;
    // draw 4 cards
    for (int i = 0; i < 4; ++i) {
    if (!deck.isEmpty()) {
        Card drawnCard = deck.drawCard();
        drawnCards.push_back(drawnCard);
    }
    }

    for (size_t i = 0; i < drawnCards.size(); ++i) {
        std::cout << "Card " << (i + 1) << ": " << drawnCards[i].getName() << " - " << drawnCards[i].getDescription() << std::endl;
    }


    while (view.isWindowOpen()) {
        handleEvents(); // Handles user interaction and window events
        update(); // Updates the game state (player, cards, etc.)
        render(); // Manages the visual display of game elements
    }

     }*/

void GameController::run() {
    MenuView menuView(view.getWindow());
    bool gameStarted = false;

    // Boucle pour l'écran d'accueil
    while (view.getWindow().isOpen() && !gameStarted) {
        sf::Event event;
        while (view.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                view.getWindow().close();
            } else if (event.type == sf::Event::MouseMoved) {
                // Mettre à jour l'état du survol
                menuView.updateHoverState(sf::Mouse::getPosition(view.getWindow()));
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (menuView.isStartButtonClicked(sf::Mouse::getPosition(view.getWindow()))) {
                    gameStarted = true;
                }
            }
        }
        menuView.render();
    }

    // Lancer le jeu après l'écran d'accueil
    deck.shuffle();
    drawnCards.clear();
    for (int i = 0; i < 4; ++i) {
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());
        }
    }

    while (view.isWindowOpen()) {
        handleEvents();
        update();
        render();
    }
}

void GameController::handleCardClick(const sf::Vector2i& mousePos) {
    float xPos = 500.0f;  // Initial X position for the cards
    float yPos = 700.0f;  // Initial Y position for the cards
    float cardWidth = 200.0f;  // Card width
    float cardHeight = 250.0f; // Card height
    float padding = 20.0f;  // Spacing between cards

    // Loop through the displayed cards
    for (size_t i = 0; i < drawnCards.size(); ++i) {
        // Calculate the area of the current card
        sf::FloatRect cardBounds(xPos, yPos, cardWidth, cardHeight);

        // Check if the mouse position is within the bounds of this card
        if (cardBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedCardIndex = static_cast<int>(i); // Update the selected card index

            // Update the situation text based on the played card
            if (drawnCards[selectedCardIndex].getType() == "Att") {
                int damage = std::stoi(drawnCards[selectedCardIndex].getValue());
                if (isArchorActive) {
                    damage *= 2;  // Double the damage
                }
                std::string situationText = "You attack the enemy with " + drawnCards[selectedCardIndex].getName() + " dealing " + std::to_string(damage) + " damage.";
                view.updateSituationText(situationText);  // Update the situation text
            } else if (drawnCards[selectedCardIndex].getType() == "HP") {
                int healing = std::stoi(drawnCards[selectedCardIndex].getValue());
                if (isVenusiaActive) {
                    healing *= 2;  // Double the healing
                }
                std::string situationText = "You heal yourself with " + drawnCards[selectedCardIndex].getName() + " restoring " + std::to_string(healing) + " health points.";
                view.updateSituationText(situationText);  // Update the situation text
            } else if (drawnCards[selectedCardIndex].getType() == "Def") {
                int defenseValue = std::stoi(drawnCards[selectedCardIndex].getValue());
                std::string situationText = "You defend yourself with " + drawnCards[selectedCardIndex].getName() +
                                             ", blocking up to " + std::to_string(defenseValue) + " damage this turn.";
                view.updateSituationText(situationText);  // Update the situation text
            } else if (drawnCards[selectedCardIndex].getType() == "Bonus") {
                std::string situationText = "You activate a bonus with " + drawnCards[selectedCardIndex].getName();
                view.updateSituationText(situationText);  // Update the situation text
            }

            return; // Stop here as a card has been selected
        }

        // Update xPos for the next card
        xPos += cardWidth + padding;
    }

    // If no card was clicked, reset the selection
    selectedCardIndex = -1;
    std::cout << "No card selected." << std::endl;
}

void GameController::handleEvents() {
    sf::Event event;
    // Poll all events from the window
    while (view.getWindow().pollEvent(event)) {
        // Handle window close event
        if (event.type == sf::Event::Closed) {
            view.getWindow().close();
        }
        // Handle mouse button press event
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Get the mouse position relative to the game window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(view.getWindow());
                // Get the position and radius of the validation circle
                sf::Vector2f circlePosition = view.getValidationCircle().getPosition();
                float radius = view.getValidationCircle().getRadius();

                // Check if the mouse click is inside the validation circle
                if (std::pow(mousePosition.x - (circlePosition.x + radius), 2) +
                    std::pow(mousePosition.y - (circlePosition.y + radius), 2) <=
                    std::pow(radius, 2)) {

                    // Handle enemy's turn if ready
                    if (isEnemyTurnReady) {
                        enemyTurn(); // Enemy executes its turn
                        isEnemyTurnReady = false; // Reset for the next round
                        canInteractWithCards = true; // Re-enable interactions after enemy's turn
                    } else {
                        // Handle end of the player's turn
                        if (selectedCardIndex >= 0 && selectedCardIndex < static_cast<int>(drawnCards.size())) {
                            playPlayerTurn(); // Execute the player's turn with the selected card

                            // If no active bonuses, switch to enemy's turn
                            if (!isArchorActive && !isVenusiaActive) {
                                isEnemyTurnReady = true;
                                view.updateSituationText("Enemy's turn. Click to continue.");
                                canInteractWithCards = false; // Disable interactions during enemy's turn
                            }
                        } else {
                            std::cout << "No card selected." << std::endl;
                        }
                    }
                }
                // Handle card interaction if not clicking on the validation circle
                else if (canInteractWithCards) {
                    handleCardClick(mousePosition); // Handle potential card click
                }
            }
        }
        // Handle keyboard input for navigation
        else if (event.type == sf::Event::KeyPressed) {
            // Allow shortcuts only when interactions are enabled
            if (canInteractWithCards) {
                if (event.key.code == sf::Keyboard::Left) {
                    // Navigate to the previous card
                    selectedCardIndex = std::max(0, selectedCardIndex - 1);
                } else if (event.key.code == sf::Keyboard::Right) {
                    // Navigate to the next card
                    selectedCardIndex = std::min(static_cast<int>(drawnCards.size() - 1), selectedCardIndex + 1);
                }
            }
        }
    }
}




// turn of the player
void GameController::playPlayerTurn() {
    // If the selected card is an attack card
    if (drawnCards[selectedCardIndex].getType() == "Att") {
        int damage = std::stoi(drawnCards[selectedCardIndex].getValue());

        // Double the damage if the Archor boost is active
        if (isArchorActive) {
            damage *= 2;
            isArchorActive = false;  // Disable the boost after the attack
        }

        // Apply the damage to the enemy
        enemy.takeDamage(damage);
        std::cout << "You attack the enemy with " << drawnCards[selectedCardIndex].getName()
                  << ", dealing " << damage << " damage." << std::endl;

    // If the selected card is a healing card
    } else if (drawnCards[selectedCardIndex].getType() == "HP") {
        int healing = std::stoi(drawnCards[selectedCardIndex].getValue());

        // Double the healing if the Venusia boost is active
        if (isVenusiaActive) {
            healing *= 2;
            isVenusiaActive = false;  // Disable the boost after the healing
        }

        // Apply the healing to the player
        player.heal(healing);
        enemy.takeDamage(0);  // The enemy doesn't take damage in this case
        std::cout << "You heal yourself with " << drawnCards[selectedCardIndex].getName()
                  << ", restoring " << healing << " HP." << std::endl;

    // If the selected card is a defense card
    } else if (drawnCards[selectedCardIndex].getType() == "Def") {
        int defenseValue = std::stoi(drawnCards[selectedCardIndex].getValue());

        // Apply the defense to the player
        player.applyDefense(defenseValue);
        enemy.takeDamage(0);  // The enemy doesn't deal damage in this case
        std::cout << "You defend yourself with " << drawnCards[selectedCardIndex].getName()
                  << ", blocking up to " << defenseValue << " damage." << std::endl;

    // If the selected card is a bonus card (Boost d'Alcor)
    } else if (drawnCards[selectedCardIndex].getType() == "Bonus" && drawnCards[selectedCardIndex].getName() == "Alcor's Boost") {
        // If the "Boost d'Alcor" card is activated
        std::cout << "You activate Alcor's Boost. You can continue playing." << std::endl;
        isArchorActive = true; // Activate the boost effect for the next turn

        // Keep the player's turn active
        view.updateHealthDisplay(player.getHealth(), enemy.getHealth());
        drawnCards.erase(drawnCards.begin() + selectedCardIndex);  // Remove the played card
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());  // Draw a new card
        }
        selectedCardIndex = -1;  // Reset the card selection
        return;  // Exit the method to prevent moving to the enemy's turn

    // If the selected card is a bonus card (Soutien de Venusia)
    } else if (drawnCards[selectedCardIndex].getType() == "Bonus" && drawnCards[selectedCardIndex].getName() == "Venusia's Support") {
        // If the "Soutien de Venusia" card is activated
        std::cout << "You activate Venusia's Support. You can continue playing." << std::endl;
        isVenusiaActive = true; // Activate the boost effect for the next turn

        // Keep the player's turn active
        view.updateHealthDisplay(player.getHealth(), enemy.getHealth());
        drawnCards.erase(drawnCards.begin() + selectedCardIndex);  // Remove the played card
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());  // Draw a new card
        }
        selectedCardIndex = -1;  // Reset the card selection
        return;  // Exit the method to prevent moving to the enemy's turn
    }
     view.updateHealthDisplay(player.getHealth(), enemy.getHealth());
        drawnCards.erase(drawnCards.begin() + selectedCardIndex);  // Remove the played card
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());  // Draw a new card
        }
        isArchorActive=false;
        isVenusiaActive=false;
        selectedCardIndex = -1;
}


void GameController::enemyTurn() {
    // Check if the enemy deck is not empty
    if (!enemyDeck.isEmpty()) {
        Card enemyCard = enemyDeck.drawCard(); // Draw a card for the enemy
        std::string enemyActionText; // Variable to store the action description

        // Check if the drawn card is an attack card
        if (enemyCard.getType() == "Att") {
            int damage = std::stoi(enemyCard.getValue()); // Convert the card value to damage
            player.takeDamage(damage); // Apply damage to the player
            enemyActionText = "The enemy attacks with " + enemyCard.getName() +
                              ", dealing " + std::to_string(damage) + " damage.";
            std::cout << enemyActionText << std::endl;

        // Check if the drawn card is a healing card
        } else if (enemyCard.getType() == "HP") {
            int healing = std::stoi(enemyCard.getValue()); // Convert the card value to healing points
            enemy.heal(healing); // Heal the enemy
            player.takeDamage(0); // No damage to the player
            enemyActionText = "The enemy heals with " + enemyCard.getName() +
                              ", restoring " + std::to_string(healing) + " health points.";
            std::cout << enemyActionText << std::endl;

        // Check if the drawn card is a defense card
        } else if (enemyCard.getType() == "Def") {
            int defenseValue = std::stoi(enemyCard.getValue()); // Convert the card value to defense points
            enemy.applyDefense(defenseValue); // Apply defense to the enemy
            player.takeDamage(0); // No damage to the player
            enemyActionText = "The enemy defends with " + enemyCard.getName() +
                              ", blocking up to " + std::to_string(defenseValue) + " damage.";
            std::cout << enemyActionText << std::endl;
        }

        // Update the health display and the situation text
        view.updateHealthDisplay(player.getHealth(), enemy.getHealth());
        view.updateSituationText(enemyActionText); // Display the enemy's action
    }
}

void GameController::update() {
    if (enemy.getHealth() <= 0) {
        std::cout << "The enemy has been defeated!" << std::endl;
        view.displayVictoryScreen();
        sf::sleep(sf::seconds(5));  // Affiche l'écran de victoire pendant 3 secondes
        view.getWindow().close();  // Ferme la fenêtre
    } else if (player.getHealth() <= 0) {
        std::cout << "You have been defeated!" << std::endl;
        view.displayDefeatScreen();
        sf::sleep(sf::seconds(5));  // Affiche l'écran de défaite pendant 3 secondes
        view.getWindow().close();  // Ferme la fenêtre
    }
}

void GameController::render() {
    // Reset the window before redrawing (clear the screen)
    view.getWindow().clear();

    // Display the player's information (e.g., showing the health)
    view.render(player, drawnCards, selectedCardIndex, enemy);

    // Render the drawn cards and highlight the selected one
    view.renderCards(   drawnCards, selectedCardIndex);


    // Display the elements on the window
    //view.getWindow().display();

   static bool isSoundPlaying = false;

    if (!isSoundPlaying) {
        PlaySound(TEXT("Intro.wav"), NULL, SND_ASYNC | SND_LOOP);  // Play sound in a loop
        isSoundPlaying = true;
    }


}
