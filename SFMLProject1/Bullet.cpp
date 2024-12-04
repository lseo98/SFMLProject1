#include "Bullet.h"
#include "iostream"

Bullet::Bullet(const sf::Vector2f startPosition, const sf::Vector2f direction, float speed)
    : Projectile(startPosition, direction, speed) {
    damage = 25.0f;
    //shape.setRadius(5.0f);         // 발사체의 크기 설정
    //shape.setFillColor(sf::Color::Magenta); // 발사체 색상 설정  
    //shape.setPosition(position);
}


void Bullet::setTexture(const sf::Texture& texture,const sf::IntRect& textureRect) {
    sprite.setTexture(texture);
    // 텍스처 영역 설정
    if (textureRect != sf::IntRect()) {
        sprite.setTextureRect(textureRect);
    }
  //  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    sprite.setScale(0.1f, 0.1f); 
    //sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    
    sprite.setPosition(position);
}


void Bullet::update() {   
    position += direction * speed;
    //std::cout << "bullet update : "<< position.x << " "<<  position.y << std::endl;
    //std::cout << "bullet update direction, speed: " << direction.x  << " "<< direction.y << " " << speed << std::endl;
    sprite.setPosition(position);

}

void Bullet::draw(sf::RenderWindow& window) {  
    window.draw(sprite);
}