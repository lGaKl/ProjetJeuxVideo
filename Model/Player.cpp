#include "Player.h"

Player::Player(int initialHealth) : health(initialHealth){}

void Player::takeDamage(int damage){
    health -= damage;
    if(health < 0) health = 0;
}

void Player::heal(int amout){
    health += amout;
}

int Player::getHealth() const{return health;}
