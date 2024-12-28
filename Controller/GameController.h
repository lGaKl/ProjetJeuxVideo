#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "EntryView.h"

class GameController {
private:
    EntryView view;

public:
    GameController();
    void run();
};

#endif // GAMECONTROLLER_H
