#include "Player.h"
#include "Bullet.h" 
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;
                         // health,  speed, sf::Vector2f position
Player::Player() : Character(3, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f)) { missileLaunched = false; }

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
    std::cout << "플레이어 체력 : " << this->health << std::endl;
}

void Player::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}

void Player::setPlayer(std::string textureFile, sf::Vector2f bulletDirection, sf::Vector2f missileDirection){

    // 공격체 방향 초기화
    this->bulletDirection = bulletDirection;
    this->missileDirection = missileDirection;


    // 플레이어 이미지 처리
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

    // 플레이어의 중앙 위치를 계산하여 총알의 시작 위치로 사용
    sf::Vector2f bulletStartPosition = this->position;
    bulletStartPosition.x += this->shape.getGlobalBounds().width / 2; // 플레이어의 중심 x 좌표
    bulletStartPosition.y += this->shape.getGlobalBounds().height / 2; // 플레이어의 중심 y 좌표

    bullets.emplace_back(bulletStartPosition, bulletDirection, 1.0f);

}



void Player::special_attack() {

    if (!missileLaunched) {                                                 // 미사일이 없는 경우
        // 플레이어의 중앙 위치를 계산하여 미사일의 시작 위치로 사용
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += this->shape.getGlobalBounds().width / 2; // 플레이어의 중심 x 좌표
        missileStartPosition.y += this->shape.getGlobalBounds().height / 2; // 플레이어의 중심 y 좌표

        missiles.emplace_back(missileStartPosition, missileDirection, 1.0f);
       // missileLaunched = true;

    }
}

void Player::ultimate_attack() {

}

void Player::updateAttack() {
    for (Bullet bullet: bullets) {
        bullet.update(); // 발사체 상태 업데이트
    }
    for (Missile missile : missiles) {
        missile.update(); // 발사체 상태 업데이트
    }
}

void Player::renderAttack(sf::RenderWindow& window) {
    for (Bullet bullet : bullets) {
        bullet.draw(window); // 발사체 상태 업데이트
    }
    for (Missile missile : missiles) {
        missile.draw(window); // 발사체 상태 업데이트
    }
}