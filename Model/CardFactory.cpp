#include "CardFactory.h"

// Méthode pour créer une carte de soin
Card CardFactory::createHealCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Retourne un objet Card pour une carte de soin
    return Card(name, description, type, points, imagePath);
}

// Méthode pour créer une carte d'attaque
Card CardFactory::createAttackCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Retourne un objet Card pour une carte d'attaque
    return Card(name, description, type, points, imagePath);
}

// Méthode pour créer une carte de défense
Card CardFactory::createDefenseCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Retourne un objet Card pour une carte de défense
    return Card(name, description, type, points, imagePath);
}

// Méthode pour créer une carte bonus
Card CardFactory::createBonusCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Retourne un objet Card pour une carte bonus
    return Card(name, description, type , points , imagePath);
}
