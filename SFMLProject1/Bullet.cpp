#include "Bullet.h"
#include "iostream"

Bullet::Bullet(const sf::Vector2f startPosition, const sf::Vector2f direction, float speed)
    : Projectile(startPosition, direction, speed) {
    damage = 100.0f;
    shape.setRadius(5.0f);         // �߻�ü�� ũ�� ����
    shape.setFillColor(sf::Color::Magenta); // �߻�ü ���� ����  
    shape.setPosition(position);
}

void Bullet::update() {
    
    position += direction * speed;
    //std::cout << "bullet update : "<< position.x << " "<<  position.y << std::endl;
    //std::cout << "bullet update direction, speed: " << direction.x  << " "<< direction.y << " " << speed << std::endl;
    shape.setPosition(position);
}

void Bullet::draw(sf::RenderWindow& window) {
   
    window.draw(shape);
}