#include "Enemy.h"
#include <iostream>
// Constructeur : Initialise l'ennemi avec des points de vie donnés
Enemy::Enemy(int initialHealth) : health(initialHealth) {}

// Retourne les points de vie actuels de l'ennemi
int Enemy::getHealth() const {
    return health;
}

// Inflige des dégâts à l'ennemi et ajuste ses points de vie
void Enemy::takeDamage(int damage) {
    std::cout << "Dégâts reçus: " << damage << std::endl;
    health -= damage;
    if (health < 0) {
        health = 0; // L'ennemi ne peut pas avoir de points de vie négatifs
    }
    std::cout << "PV restants après dégâts: " << health << std::endl;
}


// Soigne l'ennemi en augmentant ses points de vie
void Enemy::heal(int healAmount) {
    health += healAmount;
}

// Retourne vrai si l'ennemi est encore en vie
bool Enemy::isAlive() const {
    return health > 0;
}
