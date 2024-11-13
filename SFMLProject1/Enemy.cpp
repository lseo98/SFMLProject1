#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float health, float speed, sf::Vector2f position) : Character(health, speed, position), attackPattern(nullptr) {}

void Enemy::setEnemyAttack(std::unique_ptr<EnemyAttack> pattern) {
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
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}

void Enemy::image(const std::string& textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setScale(0.2f, 0.2f);  // �ʿ信 ���� ������ ����
        sprite.setTexture(texture);   // �ؽ�ó�� ��������Ʈ�� ����
    }
}