#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Deck.h"
#include "Enemy.h"
#include <random>
class GameView {
private:
    std::string chooseEnemyImage();
    sf::RenderWindow window;
    sf::Font font;
    sf::Text cardPlayedText;
    sf::CircleShape validationCircle;
    sf::RectangleShape situation;
    //sf::RectangleShape playerRect;       // Rectangle pour le joueur
    sf::Text playerNameText;             // Texte pour le nom du joueur
    sf::Text playerHealthText;
    //sf::RectangleShape enemyRect;
    sf::Text enemyNameText;              // Texte pour le nom de l'ennemi
    sf::Text enemyHealthText;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    sf::Texture backgroundTexture; // Texture pour le fond
    sf::Sprite backgroundSprite;  // Sprite pour le fond
    std::mt19937 rng;
    sf::Texture victoryTexture;
    sf::Sprite victorySprite;
    sf::Texture defeatTexture;
    sf::Sprite defeatSprite;

public:
    GameView();
    sf::RenderWindow& getWindow() { return window; }
    void render(const Player& player, const std::vector<Card>& cards,int selectedCardIndex,const Enemy& enemy);  // Méthode pour afficher le joueur et les cartes
    void renderCards(const std::vector<Card>& cards,int selectedCardIndex);
    bool isWindowOpen() const;
    void updateCardPlayedText(const Card& card);
    void displayCardPlayedText(const std::string& text);
    void updateHealthDisplay(int playerHealth, int enemyHealth);
    sf::CircleShape& getValidationCircle();
    void updateSituationText(const std::string& situationText);
    void initValidationCircle();
    void displayVictoryScreen();
    void displayDefeatScreen();
};

#endif // GAMEVIEW_H
