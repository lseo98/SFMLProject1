#include "Player.h"
#include "Bullet.h" // Bullet 클래스 포함
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

Player::Player() : attackStrategy(nullptr), Character(3, 7.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f)) {}

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
    if (attackStrategy) {
        // 플레이어의 중앙 위치를 계산하여 총알의 시작 위치로 사용
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->shape.getGlobalBounds().width / 2; // 플레이어의 중심 x 좌표
        bulletStartPosition.y += this->shape.getGlobalBounds().height / 2; // 플레이어의 중심 y 좌표

        attackStrategy->basic_attack(bulletStartPosition); // 전략에 플레이어의 중앙 위치 전달
    }
}


void Player::special_attack() {
    if (attackStrategy) {
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->shape.getGlobalBounds().width / 2;
        bulletStartPosition.y += this->shape.getGlobalBounds().height / 2;

        attackStrategy->special_attack(bulletStartPosition);
    }
}

void Player::ultimate_attack() {
    if (attackStrategy) attackStrategy->ultimate_attack();
}

void Player::setAttackStrategy(std::unique_ptr<AttackStrategy> strategy) {
    attackStrategy = std::move(strategy);
}

void Player::performBasicAttack() {
    basic_attack(); // 기본 공격 수행
}

void Player::performSpecialAttack() {
    special_attack(); // 특수 공격 수행
}
