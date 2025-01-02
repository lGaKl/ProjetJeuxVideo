#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameView.h"
#include "Player.h"
#include "Deck.h"

class GameController {
private:
    GameView view;
    Player player;
    Deck deck;
    std::vector<Card> drawnCards;

public:
    GameController();
    void run();
    void handleEvents();
    void update();
    void render();
    // Getter
    GameView& getView() { return view; }
    Player& getPlayer() { return player; }
    Deck& getDeck() { return deck; }
};

#endif // GAMECONTROLLER_H
