#include "Character.h"

Character::Character() : Character(100.0f, 1.0f, sf::Vector2f(0,0)) {}

Character::Character(float health, float speed, sf::Vector2f position) : health(health), speed(speed), position(position) {
    // ��������Ʈ ����
    //if (!texture.loadFromFile("default.png")) { /* �⺻ �ؽ�ó ���� (default.png)*/ }
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 0.2f); // �⺻ ũ�� ���� (�ʿ信 ���� ����)
    sprite.setPosition(position);
}

void Character::take_damage(float amount) {
    this->health -= amount;
    if (this->health < 0) this->health = 0;
}

void Character::draw(sf::RenderWindow& window) {
    sprite.setPosition(this->position); // ��ġ ����ȭ
    window.draw(sprite);
}

float Character::get_health() const {
    return health;
}

float Character::get_speed() const {
    return speed;
}
