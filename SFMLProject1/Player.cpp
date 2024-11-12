#include "Player.h"
#include "Bullet.h" // Bullet 클래스 포함
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

Player::Player() : attackType(nullptr), Character(3, /*speed*/ 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f)) {}

void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // 위치 업데이트

    float sizeX = this->shape.getSize().x, sizeY = this->shape.getSize().y;     // 플레이어 객채의 가로 세로 크기 추출
    // 플레이어가 설정 화면 바깥으로 나갈 경우 예외 처리
    if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
    if (this->position.x + sizeX> WINDOWWIDTH / 4.0f * 3.0f)this->position.x = WINDOWWIDTH / 4.0f * 3.0f - sizeX;
    if (this->position.y < 0)  this->position.y = 0;
    if (this->position.y + sizeY > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - sizeY;
    
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
    if (attackType) {
        // 플레이어의 중앙 위치를 계산하여 총알의 시작 위치로 사용
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->shape.getGlobalBounds().width / 2; // 플레이어의 중심 x 좌표
        bulletStartPosition.y += this->shape.getGlobalBounds().height / 2; // 플레이어의 중심 y 좌표

        attackType->basic_attack(bulletStartPosition); // 전략에 플레이어의 중앙 위치 전달
    }
}


void Player::special_attack() {
    if (attackType) {
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->shape.getGlobalBounds().width / 2;
        bulletStartPosition.y += this->shape.getGlobalBounds().height / 2;

        attackType->special_attack(bulletStartPosition);
    }
}

void Player::ultimate_attack() {
    if (attackType) attackType->ultimate_attack();
}

void Player::setPlayerAttack(std::unique_ptr<PlayerAttack> attackStageType) {
    attackType = std::move(attackStageType);
}

void Player::performBasicAttack() {
    basic_attack(); // 기본 공격 수행
}

void Player::performSpecialAttack() {
    special_attack(); // 특수 공격 수행
}
