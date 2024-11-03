#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float health, float speed) : Character(health, speed), attackPattern(nullptr) {}

void Enemy::setAttackPattern(std::unique_ptr<EnemyAttackPattern> pattern) {
    attackPattern = std::move(pattern);
}

void Enemy::attack() {
    if (attackPattern) attackPattern->attack_pattern();
}

void Enemy::take_damage(float amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}