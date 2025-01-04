#include "Enemy.h"
#include <iostream>
// Constructeur : Initialise l'ennemi avec des points de vie donnés
Enemy::Enemy(int initialHealth) : health(initialHealth),defense(0) {}

// Retourne les points de vie actuels de l'ennemi
int Enemy::getHealth() const {
    return health;
}

void Enemy::takeDamage(int damage) {
    int effectiveDamage = std::max(0, damage - defense); // Réduction par la défense
    health = std::max(0, health - effectiveDamage);      // Appliquer les dégâts restants
    std::cout << "Enemy prend " << effectiveDamage << " dégâts (Défense : " << defense << ")" << std::endl;
}


// Soigne l'ennemi en augmentant ses points de vie
void Enemy::heal(int healAmount) {
    health += healAmount;
}

// Retourne vrai si l'ennemi est encore en vie
bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::applyDefense(int defenseValue) {
    defense = defenseValue;
    health += defense;
}

void Enemy::resetDefense() {
    if (defense > 0) {
        health -= defense;
        defense = 0;
        if (health < 0) health = 0; // En cas de dépassement
    }
}
