#include "Enemy.h"
#include <iostream>
// Constructeur : Initialise l'ennemi avec des points de vie donnés
Enemy::Enemy(int initialHealth) : health(initialHealth),defense(0) {}

// Retourne les points de vie actuels de l'ennemi
int Enemy::getHealth() const {
    return health;
}

void Enemy::takeDamage(int damage) {std::cout << "Attaque ennemie: " << damage << ", Défense: " << defense << ", PV avant: " << health << std::endl;

    if (defense > 0) {
        if (damage <= defense) {
            // Si l'attaque est inférieure ou égale à la défense, la défense absorbe tous les dégâts
            std::cout << "Défense > Attaque : La défense absorbe tous les dégâts." << std::endl;
            health -= defense;
            defense = 0; // La défense est épuisée
        } else if (damage > defense) {
            // Si l'attaque est plus grande que la défense, on applique les dégâts restants
            std::cout << "Attaque > Défense : Dégâts après réduction par la défense: " << (damage - defense) << std::endl;
            health -= damage;
            defense = 0; // La défense est épuisée après avoir absorbé une partie des dégâts
        }
    } else if (damage == 0) {
        // Si l'ennemi n'attaque pas, on consomme la défense
        std::cout << "L'ennemi n'a pas attaqué : La défense est consommée sans infliger de dégâts." << std::endl;
        health -= defense;
        defense = 0; // La défense est consommée
    } else {
        // Si aucune défense, on applique directement les dégâts
        std::cout << "Aucune défense : Dégâts appliqués directement." << std::endl;
        health -= damage;
    }

    // Ne jamais laisser la santé du joueur inférieure à 0
    health = std::max(0, health);

    // Affichage pour vérifier la santé après les dégâts
    std::cout << "PV après dégâts: " << health << std::endl;
}



// Soigne l'ennemi en augmentant ses points de vie
void Enemy::heal(int healAmount) {
    health += healAmount;
    if (health > 100) health = 100;
}

// Retourne vrai si l'ennemi est encore en vie
bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::applyDefense(int defenseValue) {
    defense = defenseValue;
    health += defense;
}


