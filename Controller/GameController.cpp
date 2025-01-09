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

void GameController::run() {
    MenuView menuView(view.getWindow()); // Initialize the menu view using the main game window.
    bool gameStarted = false;           // Flag to track whether the game has started.

    // Loop for the main menu screen.
    while (view.getWindow().isOpen() && !gameStarted) {
        sf::Event event; // Event object to capture user interactions.

        // Poll events from the window.
        while (view.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close the window if the close event is triggered.
                view.getWindow().close();
            } else if (event.type == sf::Event::MouseMoved) {
                // Update the hover state of the "Start Game" button based on the mouse position.
                menuView.updateHoverState(sf::Mouse::getPosition(view.getWindow()));
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Check if the "Start Game" button is clicked.
                if (menuView.isStartButtonClicked(sf::Mouse::getPosition(view.getWindow()))) {
                    gameStarted = true; // Set the flag to start the game.
                }
            }
        }

        // Render the menu screen.
        menuView.render();
    }

    // Initialize the game once the menu screen is exited.
    deck.shuffle();               // Shuffle the deck before the game starts.
    drawnCards.clear();           // Clear any previously drawn cards.

    // Draw 4 cards from the shuffled deck for the initial hand.
    for (int i = 0; i < 4; ++i) {
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());
        }
    }

    // Main game loop.
    while (view.isWindowOpen()) {
        handleEvents(); // Handle user input and interactions.
        update();       // Update the game state.
        render();       // Render the current frame.
    }
}

// Handles the interaction when a card is clicked.
void GameController::handleCardClick(const sf::Vector2i& mousePos) {
    float xPos = 500.0f;  // Initial X position for the cards.
    float yPos = 700.0f;  // Initial Y position for the cards.
    float cardWidth = 230.0f;  // Width of each card.
    float cardHeight = 270.0f; // Height of each card.
    float padding = 20.0f;  // Space between cards.

    // Loop through all displayed cards.
    for (size_t i = 0; i < drawnCards.size(); ++i) {
        // Define the area occupied by the current card.
        sf::FloatRect cardBounds(xPos, yPos, cardWidth, cardHeight);

        // Check if the mouse click is within the bounds of the current card.
        if (cardBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedCardIndex = static_cast<int>(i); // Set the index of the selected card.

            // Update the game situation text based on the card type.
            if (drawnCards[selectedCardIndex].getType() == "Att") { // Attack card.
                int damage = std::stoi(drawnCards[selectedCardIndex].getValue());
                if (isArchorActive) {
                    damage *= 2;  // Double the damage if Archor bonus is active.
                }
                std::string situationText = "You attack the enemy with " + drawnCards[selectedCardIndex].getName() +
                                            " dealing " + std::to_string(damage) + " damage.";
                view.updateSituationText(situationText);
            } else if (drawnCards[selectedCardIndex].getType() == "HP") { // Healing card.
                int healing = std::stoi(drawnCards[selectedCardIndex].getValue());
                if (isVenusiaActive) {
                    healing *= 2;  // Double the healing if Venusia bonus is active.
                }
                std::string situationText = "You heal yourself with " + drawnCards[selectedCardIndex].getName() +
                                            " restoring " + std::to_string(healing) + " health points.";
                view.updateSituationText(situationText);
            } else if (drawnCards[selectedCardIndex].getType() == "Def") { // Defense card.
                int defenseValue = std::stoi(drawnCards[selectedCardIndex].getValue());
                std::string situationText = "You defend yourself with " + drawnCards[selectedCardIndex].getName() +
                                             ", blocking up to " + std::to_string(defenseValue) + " damage this turn.";
                view.updateSituationText(situationText);
            } else if (drawnCards[selectedCardIndex].getType() == "Bonus") { // Bonus card.
                std::string situationText = "You activate a bonus with " + drawnCards[selectedCardIndex].getName();
                view.updateSituationText(situationText);
            }

            return; // Exit once a card is selected.
        }

        // Update X position for the next card.
        xPos += cardWidth + padding;
    }

    // If no card is selected, reset the selection.
    selectedCardIndex = -1;
    std::cout << "No card selected." << std::endl;
}

// Handles all events in the game (mouse, keyboard, window actions).
void GameController::handleEvents() {
    sf::Event event;

    // Poll events from the window.
    while (view.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // Close the game window if the close event is triggered.
            view.getWindow().close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Get the mouse position relative to the game window.
                sf::Vector2i mousePosition = sf::Mouse::getPosition(view.getWindow());

                // Get the position and radius of the validation circle.
                sf::Vector2f circlePosition = view.getValidationCircle().getPosition();
                float radius = view.getValidationCircle().getRadius();

                // Check if the mouse click is inside the validation circle.
                if (std::pow(mousePosition.x - (circlePosition.x + radius), 2) +
                    std::pow(mousePosition.y - (circlePosition.y + radius), 2) <=
                    std::pow(radius, 2)) {

                    // Handle the enemy's turn if ready.
                    if (isEnemyTurnReady) {
                        enemyTurn();                  // Execute the enemy's turn.
                        isEnemyTurnReady = false;    // Reset for the next round.
                        canInteractWithCards = true; // Enable interactions for the next turn.
                    } else {
                        // Handle the player's turn if a card is selected.
                        if (selectedCardIndex >= 0 && selectedCardIndex < static_cast<int>(drawnCards.size())) {
                            playPlayerTurn(); // Execute the player's turn with the selected card.

                            // If no active bonuses, switch to the enemy's turn.
                            if (!isArchorActive && !isVenusiaActive) {
                                isEnemyTurnReady = true;
                                view.updateSituationText("Enemy's turn. Click to continue.");
                                canInteractWithCards = false; // Disable interactions during the enemy's turn.
                            }
                        } else {
                            std::cout << "No card selected." << std::endl;
                        }
                    }
                } else {
                    // Handle interactions with cards or the "Back to Menu" button.
                    if (view.getBackArrowBounds().contains(static_cast<float>(mousePosition.x),
                                                           static_cast<float>(mousePosition.y))) {
                        goToMenu(); // Navigate back to the menu.
                        return;
                    }
                    handleCardClick(mousePosition); // Handle card clicks.
                }
            }
        } else if (event.type == sf::Event::KeyPressed) {
            // Allow navigation shortcuts when interactions are enabled.
            if (canInteractWithCards) {
                if (event.key.code == sf::Keyboard::Left) {
                    // Navigate to the previous card.
                    selectedCardIndex = std::max(0, selectedCardIndex - 1);
                } else if (event.key.code == sf::Keyboard::Right) {
                    // Navigate to the next card.
                    selectedCardIndex = std::min(static_cast<int>(drawnCards.size() - 1), selectedCardIndex + 1);
                }
            }
        } else if (event.type == sf::Event::MouseMoved) {
            // Update the hover state of the validation circle based on the mouse position.
            sf::Vector2i mousePosition = sf::Mouse::getPosition(view.getWindow());
            view.updateValidationCircleHover(mousePosition);
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

// Updates the game state and checks for victory or defeat conditions.
void GameController::update() {
    // Check if the enemy has been defeated.
    if (enemy.getHealth() <= 0) {
        std::cout << "The enemy has been defeated!" << std::endl;
        displayEndScreen(true); // Display the victory screen.
    }
    // Check if the player has been defeated.
    else if (player.getHealth() <= 0) {
        std::cout << "You have been defeated!" << std::endl;
        displayEndScreen(false); // Display the defeat screen.
    }
}

// Displays the end screen based on whether the player won or lost.
void GameController::displayEndScreen(bool isVictory) {
    // Set the background image depending on the outcome.
    std::string backgroundImagePath = isVictory ? "Image/Crocofest_sexy.png" : "Image/GoldoCPC_GameOver2.png";
    EndView endView(view.getWindow(), backgroundImagePath);

    // Loop to display the end screen and handle interactions.
    while (view.getWindow().isOpen()) {
        sf::Event event;

        // Poll events from the window.
        while (view.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close the window if the close event is triggered.
                view.getWindow().close();
                return;
            }
            // Update the hover state for the "Go to Menu" button.
            else if (event.type == sf::Event::MouseMoved) {
                endView.updateHoverState(sf::Mouse::getPosition(view.getWindow()));
            }
            // Handle clicks on the "Go to Menu" button.
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (endView.isMenuButtonClicked(sf::Mouse::getPosition(view.getWindow()))) {
                    goToMenu(); // Navigate back to the main menu.
                    return;
                }
            }
        }

        // Render the end screen.
        endView.render();
    }
}

// Renders the current game state, including the player, enemy, and cards.
void GameController::render() {
    // Clear the screen to prepare for the next frame.
    view.getWindow().clear();

    // Render the player, enemy, and other UI elements.
    view.render(player, drawnCards, selectedCardIndex, enemy);

    // Render the player's cards and highlight the selected card.
    view.renderCards(drawnCards, selectedCardIndex);


    // Display the elements on the window
    //view.getWindow().display();

   static bool isSoundPlaying = false;
    // Uncomment below if audio support is added.


/*

    if (!isSoundPlaying) {
        PlaySound(TEXT("Intro.wav"), NULL, SND_ASYNC | SND_LOOP);  // Play sound in a loop.
        isSoundPlaying = true;
    }
*/
}

// Resets the game state and navigates to the main menu.
void GameController::goToMenu() {
    // Reset the game state to its initial values.
    resetGame();
    MenuView menuView(view.getWindow()); // Initialize the menu view.

    // Loop to display the menu screen and handle interactions.
    while (view.getWindow().isOpen()) {
        sf::Event event;

        // Poll events from the window.
        while (view.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close the window if the close event is triggered.
                view.getWindow().close();
                return;
            }
            // Update the hover state for the "Start Game" button.
            else if (event.type == sf::Event::MouseMoved) {
                menuView.updateHoverState(sf::Mouse::getPosition(view.getWindow()));
            }
            // Handle clicks on the "Start Game" button.
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (menuView.isStartButtonClicked(sf::Mouse::getPosition(view.getWindow()))) {
                    return; // Exit the loop to return to the game.
                }
            }
        }

        // Render the main menu.
        menuView.render();
    }
}

// Resets the game state, including the player, enemy, decks, and game variables.
void GameController::resetGame() {
     std::string enemyImage = view.chooseEnemyImage();

    // Load the enemy texture
    sf::Texture& enemyTexture = view.getEnemyTexture();
    if (!enemyTexture.loadFromFile(enemyImage)) {
        std::cerr << "Error loading the enemy texture!" << std::endl;
    }

    // Update the enemy sprite with the new texture
    view.getEnemySprite().setTexture(enemyTexture);


    // Reset the player's health.
    player = Player(100);  // Player starts with 100 health points.

    // Reset the enemy's health.
    enemy = Enemy(100);  // Enemy starts with 100 health points.

    // Clear the player's deck and rebuild it with predefined cards.
    deck.clear();

    // Add healing cards to the player's deck.
    deck.addCard(CardFactory::createHealCard("Makeshift Repair", "Restores 10 health points to Goldorak.", "HP", "10", "Image/Old.png"));
    deck.addCard(CardFactory::createHealCard("Actarus Repair", "Restores 15 health points to Goldorak.", "HP", "15", "Image/Actarus.png"));
    deck.addCard(CardFactory::createHealCard("Pr. Procyon Repair", "Restores 20 health points to Goldorak.", "HP", "20", "Image/prof.png"));

    // Duplicate some cards to ensure variety.
    deck.addCard(CardFactory::createHealCard("Makeshift Repair", "Restores 10 health points to Goldorak.", "HP", "10", "Image/Old.png"));
    deck.addCard(CardFactory::createHealCard("Actarus Repair", "Restores 15 health points to Goldorak.", "HP", "15", "Image/Actarus.png"));
    deck.addCard(CardFactory::createHealCard("Pr. Procyon Repair", "Restores 20 health points to Goldorak.", "HP", "20", "Image/prof.png"));

    // Add attack cards to the player's deck.
    deck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15", "Image/Cornofulgure.png"));
    deck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20", "Image/Fulguropoing.png"));
    deck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25", "Image/Asterohache.png"));

    // Add duplicate attack cards.
    for (int i = 0; i < 3; ++i) {
        deck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15", "Image/Cornofulgure.png"));
        deck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20", "Image/Fulguropoing.png"));
        deck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25", "Image/Asterohache.png"));
    }

    // Add defense cards to the player's deck.
    deck.addCard(CardFactory::createDefenseCard("Light Barrier", "Blocks 10 damage points.", "Def", "10", "Image/shield1.png"));
    deck.addCard(CardFactory::createDefenseCard("Energy Shield", "Blocks 15 damage points.", "Def", "15", "Image/shield2.png"));
    deck.addCard(CardFactory::createDefenseCard("Aegis Véga", "Blocks 20 damage points.", "Def", "20", "Image/shield3.png"));

    // Duplicate defense cards.
    deck.addCard(CardFactory::createDefenseCard("Light Barrier", "Blocks 10 damage points.", "Def", "10", "Image/shield1.png"));
    deck.addCard(CardFactory::createDefenseCard("Energy Shield", "Blocks 15 damage points.", "Def", "15", "Image/shield2.png"));
    deck.addCard(CardFactory::createDefenseCard("Aegis Véga", "Blocks 20 damage points.", "Def", "20", "Image/shield3.png"));

    // Add bonus cards to the player's deck.
    deck.addCard(CardFactory::createBonusCard("Alcor's Boost", "Play again immediately, and your damage will be doubled.", "Bonus", "Dmg*2", "Image/alcor.png"));
    deck.addCard(CardFactory::createBonusCard("Venusia's Support", "Doubles health restored by Goldorak for 1 turn.", "Bonus", "Hp*2", "Image/venusia.png"));

    // Clear the enemy's deck and rebuild it with similar cards.
    enemyDeck.clear();

    // Add healing, attack, and defense cards to the enemy's deck.
    for (int i = 0; i < 2; ++i) {
        enemyDeck.addCard(CardFactory::createHealCard("Makeshift Repair", "Restores 10 health points to Goldorak.", "HP", "10", "Image/Old.png"));
        enemyDeck.addCard(CardFactory::createHealCard("Actarus Repair", "Restores 15 health points to Goldorak.", "HP", "15", "Image/Actarus.png"));
        enemyDeck.addCard(CardFactory::createHealCard("Pr. Procyon Repair", "Restores 20 health points to Goldorak.", "HP", "20", "Image/prof.png"));

        enemyDeck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15", "Image/Cornofulgure.png"));
        enemyDeck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20", "Image/Fulguropoing.png"));
        enemyDeck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25", "Image/Asterohache.png"));

        enemyDeck.addCard(CardFactory::createAttackCard("Cornofulgure", "Deals 15 damage points to the enemy.", "Att", "15", "Image/Cornofulgure.png"));
        enemyDeck.addCard(CardFactory::createAttackCard("Fulguropoing", "Deals 20 damage points to the enemy.", "Att", "20", "Image/Fulguropoing.png"));
        enemyDeck.addCard(CardFactory::createAttackCard("Asterohache", "Deals 25 damage points to the enemy.", "Att", "25", "Image/Asterohache.png"));

        enemyDeck.addCard(CardFactory::createDefenseCard("Light Barrier", "Blocks 10 damage points.", "Def", "10", "Image/shield1.png"));
        enemyDeck.addCard(CardFactory::createDefenseCard("Energy Shield", "Blocks 15 damage points.", "Def", "15", "Image/shield2.png"));
        enemyDeck.addCard(CardFactory::createDefenseCard("Aegis Véga", "Blocks 20 damage points.", "Def", "20", "Image/shield3.png"));
    }

    // Shuffle both decks.
    deck.shuffle();
    enemyDeck.shuffle();

    // Clear the list of drawn cards and draw the initial hand of 4 cards.
    drawnCards.clear();
    for (int i = 0; i < 4; ++i) {
        if (!deck.isEmpty()) {
            drawnCards.push_back(deck.drawCard());
        }
    }

    // Reset game variables and states.
    selectedCardIndex = -1;
    isEnemyTurnReady = false;
    canInteractWithCards = true;
    isArchorActive = false;
    isVenusiaActive = false;

    // Print a confirmation message.
    std::cout << "Game reset complete!" << std::endl;

}
