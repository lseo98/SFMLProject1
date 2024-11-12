#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& startPosition, const sf::Vector2f& direction)
    : Projectile(startPosition, direction, 5.0f) {
    shape.setRadius(5.0f);         // �߻�ü�� ũ�� ����
    shape.setFillColor(sf::Color::Magenta); // �߻�ü ���� ����
    shape.setPosition(position);
}

void Bullet::update() {
    position += direction * speed * 2.0f;
    shape.setPosition(position);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Bullet::isOffScreen(int screenWidth, int screenHeight) const {
    return (position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight);
}
