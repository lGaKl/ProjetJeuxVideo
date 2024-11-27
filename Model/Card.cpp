#include "Card.h"

Card::Card(const std::string& name, const std::string& description, const std::string& type)
    : name(name), description(description), type(type) {}

std::string Card::getName() const{return name;}

std::string Card::getDescription() const{return description;}

std::string Card::getType() const{return type;}
