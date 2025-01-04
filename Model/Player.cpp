#include "Player.h"

Player::Player(int initialHealth) : health(initialHealth){}

void Player::takeDamage(int damage){
    health -= damage;
    if(health < 0) health = 0;
}

void Player::heal(int amount){
    health += amount;
    if (health > 100) health = 100;
}

int Player::getHealth() const{return health;}
