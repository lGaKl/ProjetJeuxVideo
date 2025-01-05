#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameView.h"
#include "Player.h"
#include "Deck.h"
#include "DeckEnemy.h"
class GameController {
private:
    int selectedCardIndex;
    GameView view;
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
    Deck& getDeck() { return deck; }
};

#endif // GAMECONTROLLER_H
