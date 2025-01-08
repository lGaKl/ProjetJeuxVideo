#ifndef END_VIEW_H
#define END_VIEW_H

#include <SFML/Graphics.hpp>

class EndView {
private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::RectangleShape menuButtonRect;
    sf::Text menuButtonText;
    bool isHovered;

public:
    EndView(sf::RenderWindow& window, const std::string& backgroundImagePath);
    void render();
    bool isMenuButtonClicked(const sf::Vector2i& mousePosition);
    void updateHoverState(const sf::Vector2i& mousePosition);
};

#endif // END_VIEW_H
