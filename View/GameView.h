#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Deck.h"

class GameView {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text playerHealthText;

public:
    GameView();
    sf::RenderWindow& getWindow() { return window; }
    void render(const Player& player);
    bool isWindowOpen() const;
};

#endif // GAMEVIEW_H
