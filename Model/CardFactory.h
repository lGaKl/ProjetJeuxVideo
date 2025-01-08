#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "Card.h"
#include <string>

// The CardFactory class provides static methods for creating different types of cards.
class CardFactory {
public:
    // Creates a healing card with the specified attributes.
    static Card createHealCard(const std::string& name, const std::string& description, const std::string& type,
                               const std::string& points, const std::string& imagePath);

    // Creates an attack card with the specified attributes.
    static Card createAttackCard(const std::string& name, const std::string& description, const std::string& type,
                                 const std::string& points, const std::string& imagePath);

    // Creates a defense card with the specified attributes.
    static Card createDefenseCard(const std::string& name, const std::string& description, const std::string& type,
                                  const std::string& points, const std::string& imagePath);

    // Creates a bonus card with the specified attributes.
    static Card createBonusCard(const std::string& name, const std::string& description, const std::string& type,
                                const std::string& points, const std::string& imagePath);
};

#endif // CARDFACTORY_H
