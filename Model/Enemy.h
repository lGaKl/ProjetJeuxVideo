#ifndef ENEMY_H
#define ENEMY_H

// The Enemy class represents the opponent in the game, managing their health and defense.
class Enemy {
public:
    // Constructor: Initializes the enemy with a specified amount of health.
    Enemy(int initialHealth);

    // Returns the current health of the enemy.
    int getHealth() const;

    // Reduces the enemy's health by a specified amount, accounting for defense.
    void takeDamage(int damage);

    // Increases the enemy's health by a specified amount.
    void heal(int healAmount);

    // Checks if the enemy is still alive (health > 0).
    bool isAlive() const;

    // Sets the enemy's defense value to mitigate incoming damage.
    void applyDefense(int defenseValue);

private:
    int health;  // Current health points of the enemy.
    int defense; // Current defense points of the enemy.
};

#endif
