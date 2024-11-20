#include "Player.h"
#include "Bullet.h" 
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

Player::Player() : attackType(nullptr), Character(3, /*speed*/ 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f)) {}

void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // 위치 업데이트

    // 스프라이트의 글로벌 바운드를 사용하여 크기 추출
    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
    float sizeX = spriteBounds.width;
    float sizeY = spriteBounds.height;

    // 플레이어가 설정 화면 바깥으로 나갈 경우 예외 처리
    if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
    if (this->position.x + sizeX> WINDOWWIDTH / 4.0f * 3.0f)this->position.x = WINDOWWIDTH / 4.0f * 3.0f - sizeX;
    if (this->position.y < 0)  this->position.y = 0;
    if (this->position.y + sizeY > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - sizeY;
    
    // 스프라이트 위치를 업데이트 (position에 따라 이동)
    this->sprite.setPosition(this->position);
}

void Player::take_damage(float amount) {
    this->health -= amount;
    if (this->health < 0) this->health = 0;
}

void Player::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}

void Player::image(std::string textureFile) {
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
    if (attackType) {
         // 스프라이트의 글로벌 바운드를 사용하여 중앙 위치 계산
        sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();

        sf::Vector2f bulletStartPosition;
        bulletStartPosition.x = this->position.x + spriteBounds.width / 2; // 스프라이트 중심 x 좌표
        bulletStartPosition.y = this->position.y + spriteBounds.height / 2; // 스프라이트 중심 y 좌표
        
        attackType->basic_attack(bulletStartPosition);
    }
}


void Player::special_attack() {
    if (attackType) {
        sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();

        sf::Vector2f bulletStartPosition;
        bulletStartPosition.x = this->position.x + spriteBounds.width / 2;
        bulletStartPosition.y = this->position.y + spriteBounds.height / 2;

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
