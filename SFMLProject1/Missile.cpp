#include "Missile.h"

Missile::Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : Projectile(startPosition, direction, 8.0f) { // ¼Óµµ 8.0f 
    damage = 200.0f;
    range = 200.0f;
    shape.setRadius(10.0f);
    shape.setFillColor(sf::Color::Yellow);
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

