#include "Character.h"

Character::Character() : Character(100.0f, 1.0f, sf::Vector2f(0,0)) {
   
}

Character::Character(float health, float speed, sf::Vector2f position) : health(health), speed(speed), position(position) {
   // shape.setSize(sf::Vector2f(50, 50));  // ������ ũ�� ����
   // shape.setFillColor(sf::Color::Blue);  // ������ ���� ����
}

void Character::take_damage(float amount) {
    this->health -= amount;
    if (this->health < 0) this->health = 0;
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
