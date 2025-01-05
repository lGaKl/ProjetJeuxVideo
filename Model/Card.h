#ifndef CARD_H_
#define CARD_H_

#include <string>
#include <SFML/Graphics.hpp>
class Card {
private:
    std::string name;
    std::string description;
    std::string type;
    std::string value;
    sf::Texture cardTexture;

public:
    Card(const std::string& name, const std::string& description, const std::string& type, const std::string& value, const std::string& imagePath = "");
    std::string getName() const;
    std::string getDescription() const;
    std::string getType() const;
    std::string getValue() const;
    int getAttackValue() const;
    int getHealValue() const;
    int getDefenseValue() const;
    const sf::Texture& getTexture() const;
};

#endif // CARD_H_
