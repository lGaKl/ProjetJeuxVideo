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

public:
    GameController();
    void run();
};

#endif // GAMECONTROLLER_H
