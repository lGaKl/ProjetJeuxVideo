// Method to create a heal card
Card CardFactory::createHealCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Returns a Card object for a heal card
    return Card(name, description, type, points, imagePath);
}

// Method to create an attack card
Card CardFactory::createAttackCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Returns a Card object for an attack card
    return Card(name, description, type, points, imagePath);
}

// Method to create a defense card
Card CardFactory::createDefenseCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Returns a Card object for a defense card
    return Card(name, description, type, points, imagePath);
}

// Method to create a bonus card
Card CardFactory::createBonusCard(const std::string& name, const std::string& description, const std::string& type, const std::string& points, const std::string& imagePath) {
    // Returns a Card object for a bonus card
    return Card(name, description, type , points , imagePath);
}
