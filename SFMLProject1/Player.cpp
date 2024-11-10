#include "Player.h"
#include "Bullet.h" // Bullet Ŭ���� ����
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
        // �÷��̾��� �߾� ��ġ�� ����Ͽ� �Ѿ��� ���� ��ġ�� ���
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->shape.getGlobalBounds().width / 2; // �÷��̾��� �߽� x ��ǥ
        bulletStartPosition.y += this->shape.getGlobalBounds().height / 2; // �÷��̾��� �߽� y ��ǥ

        attackStrategy->basic_attack(bulletStartPosition); // ������ �÷��̾��� �߾� ��ġ ����
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
    basic_attack(); // �⺻ ���� ����
}

void Player::performSpecialAttack() {
    special_attack(); // Ư�� ���� ����
}
