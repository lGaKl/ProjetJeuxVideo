#ifndef PLAYER_H
#define PLAYER_H

// The Player class represents the player in the game, managing their health and defense values.
class Player {
private:
    int health;  // Current health points of the player.
    int defense; // Current defense points of the player.

public:
    // Constructor: Initializes the player with a specified amount of health.
    Player(int initialHealth);

    // Reduces the player's health by a specified amount, accounting for defense.
    void takeDamage(int damage);

    // Increases the player's health by a specified amount.
    void heal(int amount);

    // Returns the current health of the player.
    int getHealth() const;

    // Sets the player's defense value to mitigate incoming damage.
    void applyDefense(int defenseValue);
};

#endif // PLAYER_H
