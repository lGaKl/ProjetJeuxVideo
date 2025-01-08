#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameView.h"
#include "MenuView.h"
#include "EndView.h"
#include "Player.h"
#include "Deck.h"
#include "DeckEnemy.h"
class GameController {
private:
    int selectedCardIndex;
    GameView view;
    //MenuView menuView;
    Player player;
    Deck deck;
    DeckEnemy enemyDeck;
    std::vector<Card> drawnCards;
    sf::Clock clock;


public:
    GameController();
    void run();
    void handleEvents();
    void update();
    void render();

    void handleCardClick(const sf::Vector2i& mousePos);

    void enemyTurn();
    void playPlayerTurn();
    // Getter
    GameView& getView() { return view; }
    Player& getPlayer() { return player; }
    //Deck& getDeck() { return deck; }
    //MenuView& getMenuView { return menuView;}
    void goToMenu();
    void resetGame();
    void displayEndScreen(bool isVictory);
};

#endif // GAMECONTROLLER_H
