#include "Player.h"
#include <iostream>

Player::Player() : attackStrategy(nullptr) {}

void Player::setAttackStrategy(std::unique_ptr<AttackStrategy> strategy) {
    attackStrategy = std::move(strategy);
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

void Player::take_damage(float amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}