#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    // Constructeur qui prend en argument les points de vie initiaux
    Enemy(int initialHealth);

    // Accesseur pour obtenir les points de vie actuels de l'ennemi
    int getHealth() const;

    // Méthode pour infliger des dégâts à l'ennemi
    void takeDamage(int damage);

    // Méthode pour soigner l'ennemi
    void heal(int healAmount);

    // Méthode pour savoir si l'ennemi est vivant
    bool isAlive() const;
    void applyDefense(int defenseValue);
    void resetDefense() ;

private:
    int health;  // Points de vie de l'ennemi
    int defense;
};

#endif
