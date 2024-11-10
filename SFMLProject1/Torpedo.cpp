#include "Torpedo.h"

Torpedo::Torpedo(const sf::Vector2f& startPosition)
    : Projectile(startPosition, sf::Vector2f(1.0f, 0.0f), 6.0f) { // 오른쪽 방향, 속도 6.0f
    shape.setRadius(8.0f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
}

void Torpedo::update() {
    adjustDirection();
    position += direction * speed;
    shape.setPosition(position);
}

void Torpedo::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Torpedo::isOffScreen(int screenWidth, int screenHeight) const {
    return (position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight);
}



