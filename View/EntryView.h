#ifndef ENTRYVIEW_H
#define ENTRYVIEW_H

#include <SFML/Graphics.hpp>
#include "ViewManager.h"

class EntryView {
private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape startButton;
    sf::Text buttonText;
    sf::Font font;

public:
    EntryView();
    sf::RenderWindow& getWindow() { return window; }
    sf::RectangleShape& getButton();
    void render();
    bool isWindowOpen() const;
    void loadBackground(const std::string& filePath);
    void setupButton();
    bool isButtonClicked(const sf::Vector2f& mousePos); //pour vérif si le bouton est cliqué
    bool isButtonHovered(const sf::Vector2f& mousePos); // Vérifie si la souris est au-dessus du bouton
    void resizeElements();
};

#endif // ENTRYVIEW_H
