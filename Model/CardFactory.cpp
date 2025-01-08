#include "CardFactory.h"

// Creates a healing card.
Card CardFactory::createHealCard(const std::string& name, const std::string& description, const std::string& type,
                                 const std::string& points, const std::string& imagePath) {
    return Card(name, description, type, points, imagePath);
}

// Creates an attack card.
Card CardFactory::createAttackCard(const std::string& name, const std::string& description, const std::string& type,
                                   const std::string& points, const std::string& imagePath) {
    return Card(name, description, type, points, imagePath);
}

// Creates a defense card.
Card CardFactory::createDefenseCard(const std::string& name, const std::string& description, const std::string& type,
                                    const std::string& points, const std::string& imagePath) {
    return Card(name, description, type, points, imagePath);
}

// Creates a bonus card.
Card CardFactory::createBonusCard(const std::string& name, const std::string& description, const std::string& type,
                                  const std::string& points, const std::string& imagePath) {
    return Card(name, description, type, points, imagePath);
}
