#include "Enemy.h"
#include <iostream>


//This class manages the health, defense, and interactions of the enemy with attacks, healing, and defense management in the game.
// Constructor: Initializes the enemy with given health points
Enemy::Enemy(int initialHealth) : health(initialHealth),defense(0) {}

// Returns the current health points of the enemy
int Enemy::getHealth() const {
    return health;
}

void Enemy::takeDamage(int damage) {
    std::cout << "Enemy attack: " << damage << ", Defense: " << defense << ", Health before: " << health << std::endl;

    if (defense > 0) {
        if (damage <= defense) {
            // If the attack is less than or equal to the defense, the defense absorbs all the damage
            std::cout << "Defense > Attack: Defense absorbs all the damage." << std::endl;
            health -= defense;
            defense = 0; // Defense is used up
        } else if (damage > defense) {
            // If the attack is greater than the defense, apply the remaining damage
            std::cout << "Attack > Defense: Damage after defense reduction: " << (damage - defense) << std::endl;
            health -= damage;
            defense = 0; // Defense is used up after absorbing part of the damage
        }
    } else if (damage == 0) {
        // If the enemy does not attack, the defense is consumed
        std::cout << "Enemy did not attack: Defense is consumed without damage." << std::endl;
        health -= defense;
        defense = 0; // Defense is consumed
    } else {
        // If no defense, apply the damage directly
        std::cout << "No defense: Damage applied directly." << std::endl;
        health -= damage;
    }

    // Never let the health be less than 0
    health = std::max(0, health);

    // Display to verify health after damage
    std::cout << "Health after damage: " << health << std::endl;
}



// Heals the enemy by increasing their health points
void Enemy::heal(int healAmount) {
    health += healAmount;
    if (health > 100) health = 100;
}

// Returns true if the enemy is still alive
bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::applyDefense(int defenseValue) {
    defense = defenseValue;
    health += defense;
}


