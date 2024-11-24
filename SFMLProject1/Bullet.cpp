#include "Bullet.h"
#include "iostream"

Bullet::Bullet(const sf::Vector2f startPosition, const sf::Vector2f direction, float speed)
    : Projectile(startPosition, direction, speed) {
    shape.setRadius(5.0f);         // 발사체의 크기 설정
    shape.setFillColor(sf::Color::Magenta); // 발사체 색상 설정  
    shape.setPosition(position);
}

void Bullet::update() {

    position += direction * speed;

    shape.setPosition(position);
}

void Bullet::draw(sf::RenderWindow& window) {
   
    window.draw(shape);
}