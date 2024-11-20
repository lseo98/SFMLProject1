#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : Projectile(startPosition, direction, speed) {
    shape.setRadius(5.0f);         // �߻�ü�� ũ�� ����
    shape.setFillColor(sf::Color::Magenta); // �߻�ü ���� ����
    shape.setPosition(position);
}

void Bullet::update() {
    position += direction * speed * 4.0f;
    shape.setPosition(position);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
