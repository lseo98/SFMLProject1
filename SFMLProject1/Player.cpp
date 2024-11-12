#include "Player.h"
#include "Bullet.h" // Bullet Ŭ���� ����
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

Player::Player()
    : attackStrategy(nullptr), Character(3, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f))  
{

    // ���������� �´� �̹��� ���� ��� ����s
    std::string textureFile;
 

    if (!texture.loadFromFile(textureFile)) { // �̹��� ���� �ε�
        std::cerr << "Error loading player texture: " << textureFile << std::endl;
    }
    else {
        sprite.setScale(0.1f, 0.1f);
        sprite.setTexture(texture);                // �ؽ�ó�� ��������Ʈ�� ����       
        sprite.setPosition(position);              // �ʱ� ��ġ ����
    }
}

// ���������� ���� �̹��� ������Ʈ�ϴ� ��� �Լ�
void Player::setStage(int stageNumber) {
    std::string textureFile;
    switch (stageNumber) {
    case 1:
        textureFile = "sky_my_unit.png";  // �ϴ� �������� �̹���
        break;
    case 2:
        textureFile = "sea_my_unit.png";  // �ٴ� �������� �̹���
        break;
    case 3:
        textureFile = "land_my_unit.png"; // �� �������� �̹���
        break;
    }

    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading player texture: " << textureFile << std::endl;
    }
    else {
        sprite.setTexture(texture);  // �ؽ�ó�� ��������Ʈ�� ����
    }
    Player();
}

void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // ��ġ ������Ʈ

   // float sizeX = this->shape.getSize().x, sizeY = this->shape.getSize().y;     // �÷��̾� ��ä�� ���� ���� ũ�� ����


    float sizeX = sprite.getGlobalBounds().width;
    float sizeY = sprite.getGlobalBounds().height;
   // �÷��̾ ���� ȭ�� �ٱ����� ���� ��� ���� ó��
    if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
    if (this->position.x + sizeX> WINDOWWIDTH / 4.0f * 3.0f)this->position.x = WINDOWWIDTH / 4.0f * 3.0f - sizeX;
    if (this->position.y < 0)  this->position.y = 0;
    if (this->position.y + sizeY > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - sizeY;

    sprite.setPosition(position); // ��������Ʈ�� ��ġ ������Ʈ

}

void Player::take_damage(float amount) {
    this->health -= amount;
    if (this->health < 0) this->health = 0;
}

void Player::draw(sf::RenderWindow& window) {
   // this->shape.setPosition(this->position);
    //window.draw(this->shape);
    window.draw(sprite); // ��������Ʈ�� �׸���

}

void Player::basic_attack() {
    if (attackStrategy) {
        // �÷��̾��� �߾� ��ġ�� ����Ͽ� �Ѿ��� ���� ��ġ�� ���
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->sprite.getGlobalBounds().width / 2; // �÷��̾��� �߽� x ��ǥ
        bulletStartPosition.y += this->sprite.getGlobalBounds().height / 5; // �÷��̾��� �߽� y ��ǥ

        attackStrategy->basic_attack(bulletStartPosition); // ������ �÷��̾��� �߾� ��ġ ����
    }
}


void Player::special_attack() {
    if (attackStrategy) {
        sf::Vector2f bulletStartPosition = this->position;
        bulletStartPosition.x += this->sprite.getGlobalBounds().width / 2;
        bulletStartPosition.y += this->sprite.getGlobalBounds().height / 2;

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
