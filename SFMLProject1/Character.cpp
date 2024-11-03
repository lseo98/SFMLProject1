#include "Character.h"

Character::Character() : health(100.0f), speed(1.0f) {
    shape.setSize(sf::Vector2f(50, 50));  // 임의의 크기 설정
    shape.setFillColor(sf::Color::Blue);  // 임의의 색상 설정
}

Character::Character(float health, float speed)
    : health(health), speed(speed) {
    shape.setSize(sf::Vector2f(50, 50));  // 임의의 크기 설정
    shape.setFillColor(sf::Color::Blue);  // 임의의 색상 설정
}

void Character::take_damage(float amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Character::get_health() const {
    return health;
}

float Character::get_speed() const {
    return speed;
}
