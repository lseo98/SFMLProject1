#include "Player.h"
#include "Bullet.h" 
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;
                         // health,  speed, sf::Vector2f position
Player::Player() : Character(3, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f)) { missileLaunched = false; }

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
    std::cout << "�÷��̾� ü�� : " << this->health << std::endl;
}

void Player::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}

void Player::setPlayer(std::string textureFile, sf::Vector2f bulletDirection, sf::Vector2f missileDirection){

    // ����ü ���� �ʱ�ȭ
    this->bulletDirection = bulletDirection;
    this->missileDirection = missileDirection;


    // �÷��̾� �̹��� ó��
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setScale(0.1f, 0.1f);
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }
}

void Player::basic_attack() {

    // �÷��̾��� �߾� ��ġ�� ����Ͽ� �Ѿ��� ���� ��ġ�� ���
    sf::Vector2f bulletStartPosition = this->position;
    bulletStartPosition.x += this->shape.getGlobalBounds().width / 2; // �÷��̾��� �߽� x ��ǥ
    bulletStartPosition.y += this->shape.getGlobalBounds().height / 2; // �÷��̾��� �߽� y ��ǥ

    bullets.emplace_back(bulletStartPosition, bulletDirection, 1.0f);

}



void Player::special_attack() {

    if (!missileLaunched) {                                                 // �̻����� ���� ���
        // �÷��̾��� �߾� ��ġ�� ����Ͽ� �̻����� ���� ��ġ�� ���
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += this->shape.getGlobalBounds().width / 2; // �÷��̾��� �߽� x ��ǥ
        missileStartPosition.y += this->shape.getGlobalBounds().height / 2; // �÷��̾��� �߽� y ��ǥ

        missiles.emplace_back(missileStartPosition, missileDirection, 1.0f);
       // missileLaunched = true;

    }
}

void Player::ultimate_attack() {

}

void Player::updateAttack() {
    for (Bullet bullet: bullets) {
        bullet.update(); // �߻�ü ���� ������Ʈ
    }
    for (Missile missile : missiles) {
        missile.update(); // �߻�ü ���� ������Ʈ
    }
}

void Player::renderAttack(sf::RenderWindow& window) {
    for (Bullet bullet : bullets) {
        bullet.draw(window); // �߻�ü ���� ������Ʈ
    }
    for (Missile missile : missiles) {
        missile.draw(window); // �߻�ü ���� ������Ʈ
    }
}