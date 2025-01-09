#include "Card.h"
#include <iostream>

// The Card class represents a card in the game, with attributes such as name, description, type, value, and an optional image.
Card::Card(const std::string& name, const std::string& description, const std::string& type, const std::string& value,
           const std::string& imagePath)
    : name(name), description(description), type(type), value(value) {
    if (!imagePath.empty()) {
        // Load the card image if a valid path is provided.
        if (!cardTexture.loadFromFile(imagePath)) {
            std::cerr << "Error loading image: " << imagePath << std::endl; // Handle image loading errors.
        }
    }
}

// Returns the card's name.
std::string Card::getName() const { return name; }

// Returns the card's description.
std::string Card::getDescription() const { return description; }

// Returns the card's type (e.g., "Att", "Def", "HP", "Bonus").
std::string Card::getType() const { return type; }

// Returns the card's value as a string.
std::string Card::getValue() const { return value; }

// Returns the attack value of the card, or 0 if the card is not of type "Att".
int Card::getAttackValue() const {
    if (type == "Att") {
        return std::stoi(value);
    }
    return 0;
}

// Returns the healing value of the card, or 0 if the card is not of type "HP".
int Card::getHealValue() const {
    if (type == "Soin") {
        return std::stoi(value);
    }
    return 0;
}

// Returns the defense value of the card, or 0 if the card is not of type "Def".
int Card::getDefenseValue() const {
    if (type == "Def") {
        return std::stoi(value);
    }
    return 0;
}

// Returns the texture of the card (used for rendering the card's image).
const sf::Texture& Card::getTexture() const {
    return cardTexture;
}
