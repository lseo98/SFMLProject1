#include "Missile.h"

Missile::Missile(const sf::Vector2f& startPosition)
    : Projectile(startPosition, sf::Vector2f(0.0f, -1.0f), 8.0f) { // 속도 8.0f로 위쪽 방향
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

bool Missile::isOffScreen(int screenWidth, int screenHeight) const {
    return (position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight);
}
