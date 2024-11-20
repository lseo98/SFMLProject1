#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float health, float speed, sf::Vector2f position) : Character(health, speed, position){}

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




// EliteUnit

void EliteUnit::special_attack() {
    if (!missileLaunched) {                                                 // �̻����� ���� ���
        // ������ �߾� ��ġ�� ����Ͽ� �̻����� ���� ��ġ�� ���
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += this->shape.getGlobalBounds().width / 2; // �÷��̾��� �߽� x ��ǥ
        missileStartPosition.y += this->shape.getGlobalBounds().height / 2; // �÷��̾��� �߽� y ��ǥ

        missiles.emplace_back(missileStartPosition, missileDirection, 1.0f);
        // missileLaunched = true;

    }
}

void EliteUnit::updateAttack() {
    
    for (Missile missile : missiles) {
        missile.update(); // �߻�ü ���� ������Ʈ
    }
}

void EliteUnit::renderAttack(sf::RenderWindow& window) {

    for (Missile missile : missiles) {
        missile.draw(window); // �߻�ü ���� ������Ʈ
    }
}