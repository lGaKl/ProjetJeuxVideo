#include "Player.h"
#include <iostream>
Player::Player(int initialHealth) : health(initialHealth),defense(0) {}


void Player::takeDamage(int damage) {
    // Réduction des dégâts par le bouclier
    int effectiveDamage = std::max(0, damage - defense);

    // Réduction de la vie après application du bouclier
    health = std::max(0, health - effectiveDamage);

    // Réduction du bouclier (reste à 0 si négatif)
    defense = std::max(0, defense - damage);

    // Afficher les informations
    std::cout << "Player prend " << effectiveDamage
              << " dégâts (PV : " << health << ", Bouclier restant : " << defense << ")"
              << std::endl;
}
void Player::heal(int amount){
    health += amount;
    if (health > 100) health = 100;
}

void Player::applyDefense(int defenseValue) {
    defense = defenseValue;
    health += defense;
}

void Player::resetDefense() {
    // Si la défense est positive, on ajuste les points de vie
    if (defense > 0) {
        // Réduire les points de vie si les dégâts surpassent le bouclier
        int remainingDamage = -defense; // Le surplus de dégâts non absorbés
        health = std::max(0, health - std::max(0, remainingDamage));

        // Réinitialiser la défense à 0
        defense = 0;
    }
}

int Player::getHealth() const{return health;}
