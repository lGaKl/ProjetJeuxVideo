#include "Card.h"

Card::Card(const std::string& name, const std::string& description, const std::string& type, const std::string& value)
    : name(name), description(description), type(type), value(value) {}

std::string Card::getName() const{return name;}

std::string Card::getDescription() const{return description;}

std::string Card::getType() const{return type;}

std::string Card::getValue() const{return value;}

int Card::getAttackValue() const {
    if (type == "Att") {
        return std::stoi(value); // Conversion de la valeur en entier
    }
    return 0; // Pas une carte d'attaque
}

int Card::getHealValue() const {
    if (type == "Soin") {
        return std::stoi(value); // Conversion de la valeur en entier
    }
    return 0;
}

int Card::getDefenseValue() const {
    if (type == "Def") {
        return std::stoi(value); // Conversion de la valeur en entier
    }
    return 0;
}
