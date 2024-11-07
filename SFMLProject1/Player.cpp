#include "Player.h"
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

Player::Player() : attackStrategy(nullptr), Character(3, 7.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f)) {  }


void Player::move(sf::Vector2f updatePosition) {
   
    this->position += updatePosition;
}

void Player::take_damage(float amount) {
    this->health -= amount;
    if (this->health < 0) this->health = 0;
}

void Player::draw(sf::RenderWindow& window) {
    this->shape.setPosition(this->position);
    window.draw(this->shape);
}

void Player::basic_attack() {
    if (attackStrategy) attackStrategy->basic_attack();
}

void Player::special_attack() {
    if (attackStrategy) attackStrategy->special_attack();
}

void Player::ultimate_attack() {
    if (attackStrategy) attackStrategy->ultimate_attack();
}

void Player::setAttackStrategy(std::unique_ptr<AttackStrategy> strategy) {
    attackStrategy = std::move(strategy);
}


