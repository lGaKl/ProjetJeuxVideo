#ifndef PLAYER_H
#define PLAYER_H

class Player{
private:
    int health;

public:
    Player(int initialHealth);
    void takeDamage(int damage);
    void heal(int amout);
    int getHealth() const;
};

#endif // PLAYER_H
