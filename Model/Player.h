#ifndef PLAYER_H
#define PLAYER_H

class Player{
private:
    int health;
    int defense;
public:
    Player(int initialHealth);
    void takeDamage(int damage);
    void heal(int amout);
    int getHealth() const;
    void applyDefense(int defenseValue);

    // Méthode pour réinitialiser la défense temporaire
    void resetDefense();
};

#endif // PLAYER_H
