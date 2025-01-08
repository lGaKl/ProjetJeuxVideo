#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "GameView.h"
#include "Player.h"
#include "Deck.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class MenuView {
private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text startButtonText;
    sf::RectangleShape startButtonRect;
    bool isHovered;

public:
    MenuView(sf::RenderWindow& window);
    void render();
    bool isStartButtonClicked(const sf::Vector2i& mousePosition);
    void updateHoverState(const sf::Vector2i& mousePosition);
};

#endif // MENU_VIEW_H
