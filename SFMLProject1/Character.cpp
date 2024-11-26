#include "Character.h"

Character::Character() : Character(100.0f, 1.0f, sf::Vector2f(0,0)) {}

Character::Character(float health, float speed, sf::Vector2f position) : health(health), speed(speed), position(position) {

     // 스프라이트 설정
    //if (!texture.loadFromFile("default.png")) { /* 기본 텍스처 파일 (default.png)*/ }
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 0.2f); // 기본 크기 조정 (필요에 따라 조정)
    sprite.setPosition(position);

    // shape.setSize(sf::Vector2f(50, 50));  // 임의의 크기 설정
   // shape.setFillColor(sf::Color::Blue);  // 임의의 색상 설정
}

void Character::setPosition(sf::Vector2f postion) {
    this->position = postion;
}

void Character::take_damage(float amount) {
    this->health -= amount;
    if (this->health < 0) this->health = 0;

}

void Character::draw(sf::RenderWindow& window) {
    sprite.setPosition(this->position); // 위치 동기화
    window.draw(sprite);
}

float Character::get_health() const {
    return health;
}

float Character::get_speed() const {
    return speed;
}
