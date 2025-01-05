#include "Player.h"
#include <iostream>
//The Player class manages a player's health, defense, and interactions with damage, healing, and defense application in the game.
Player::Player(int initialHealth) : health(initialHealth),defense(0) {}


void Player::takeDamage(int damage) {
    // Display to check initial values
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
        // If the enemy doesn't attack, the defense is consumed
        std::cout << "Enemy did not attack: Defense is consumed without damage." << std::endl;
        health -= defense;
        defense = 0; // Defense is consumed
    } else {
        // If no defense, apply the damage directly
        std::cout << "No defense: Damage applied directly." << std::endl;
        health -= damage;
    }

    // Never let the player's health go below 0
    health = std::max(0, health);

    // Display to verify health after damage
    std::cout << "Health after damage: " << health << std::endl;
}




void Player::heal(int amount){
    health += amount;
    if (health > 100) health = 100;
}

void Player::applyDefense(int defenseValue) {
    defense = defenseValue;
    health += defense;
}



int Player::getHealth() const{return health;}
