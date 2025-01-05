#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "Card.h"
#include <string>

class CardFactory {
public:
    // Méthodes statiques pour créer différents types de cartes
    static Card createHealCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath);
    static Card createAttackCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath);
    static Card createDefenseCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath);
    static Card createBonusCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath);
};

#endif // CARDFACTORY_H
