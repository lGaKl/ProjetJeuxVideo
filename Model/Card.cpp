#include "Card.h"
#include <iostream>

// The Card class represents a card in the game, with each card having a name, description, type, and associated value.
// The cards can be of type "Atk" (Attack), "Def" (Defense), "Heal" (Healing), or "Bonus".
  Card::Card(const std::string& name, const std::string& description, const std::string& type, const std::string& value, const std::string& imagePath)
    : name(name), description(description), type(type), value(value) {
    if (!imagePath.empty()) {
        // Chargement de l'image associée à la carte si un chemin est fourni
        if (!cardTexture.loadFromFile(imagePath)) {
            // Gestion d'erreur si l'image ne se charge pas
            std::cerr << "Erreur de chargement de l'image: " << imagePath << std::endl;
        }
    }
}

std::string Card::getName() const{return name;}

std::string Card::getDescription() const{return description;}

std::string Card::getType() const{return type;}

std::string Card::getValue() const{return value;}

int Card::getAttackValue() const {
    if (type == "Att") {
        return std::stoi(value);
    }
    return 0;
}

int Card::getHealValue() const {
    if (type == "Soin") {
        return std::stoi(value);
    }
    return 0;
}


int Card::getDefenseValue() const {
    if (type == "Def") {
        return std::stoi(value);
    }
    return 0;
}

const sf::Texture& Card::getTexture() const {
    return cardTexture;
}
