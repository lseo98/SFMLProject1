#include "Enemy.h"
#include <iostream>　

Enemy::Enemy(float health, float speed, sf::Vector2f position,const std::string& textureFile)
    : Character(health, speed, position), attackPattern(nullptr)
{
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }
}

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
    sprite.setPosition(position);  // 현재 위치에 스프라이트 설정

    window.draw(sprite);
}