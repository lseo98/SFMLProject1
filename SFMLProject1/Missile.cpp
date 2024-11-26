#include "Missile.h"

Missile::Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : Projectile(startPosition, direction, speed) { // �ӵ� 8.0f�� ���� ����
    shape.setRadius(7.0f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(position);
}

void Missile::update() {
    adjustDirection(); 
    position += direction * speed;
    shape.setPosition(position);
}

void Missile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

