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
        sprite.setScale(0.2f, 0.2f);  // 필요에 따라 스케일 조정
        sprite.setTexture(texture);   // 텍스처를 스프라이트에 적용
    }
}




// EliteUnit

void EliteUnit::special_attack() {
    if (!missileLaunched) {                                                 // 미사일이 없는 경우
        // 유닛의 중앙 위치를 계산하여 미사일의 시작 위치로 사용
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += this->shape.getGlobalBounds().width / 2; // 플레이어의 중심 x 좌표
        missileStartPosition.y += this->shape.getGlobalBounds().height / 2; // 플레이어의 중심 y 좌표

        missiles.emplace_back(missileStartPosition, missileDirection, 1.0f);
        // missileLaunched = true;

    }
}

void EliteUnit::updateAttack() {
    
    for (Missile missile : missiles) {
        missile.update(); // 발사체 상태 업데이트
    }
}

void EliteUnit::renderAttack(sf::RenderWindow& window) {

    for (Missile missile : missiles) {
        missile.draw(window); // 발사체 상태 업데이트
    }
}