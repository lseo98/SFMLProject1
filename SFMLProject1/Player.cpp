#include "Player.h"
#include "Bullet.h" // Bullet Ŭ���� ����
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

Player::Player() : attackType(nullptr), Character(3, /*speed*/ 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f)) {}

void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // ��ġ ������Ʈ

    float sizeX = this->shape.getSize().x, sizeY = this->shape.getSize().y;     // �÷��̾� ��ä�� ���� ���� ũ�� ����
    // �÷��̾ ���� ȭ�� �ٱ����� ���� ��� ���� ó��
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
        // �÷��̾��� �߾� ��ġ�� ����Ͽ� �Ѿ��� ���� ��ġ�� ���
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->shape.getGlobalBounds().width / 2; // �÷��̾��� �߽� x ��ǥ
        bulletStartPosition.y += this->shape.getGlobalBounds().height / 2; // �÷��̾��� �߽� y ��ǥ

        attackType->basic_attack(bulletStartPosition); // ������ �÷��̾��� �߾� ��ġ ����
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
    basic_attack(); // �⺻ ���� ����
}

void Player::performSpecialAttack() {
    special_attack(); // Ư�� ���� ����
}
