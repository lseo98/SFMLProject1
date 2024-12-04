#include "Missile.h"

Missile::Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : Projectile(startPosition, direction, 8.0f) { // 속도 8.0f 
    damage = 200.0f;
    range = 200.0f;
  //  shape.setRadius(10.0f);
   // shape.setFillColor(sf::Color::Yellow); 
   // shape.setPosition(position);
}
void Missile::setTexture(const sf::Texture& texture, const sf::IntRect& textureRect) {
    sprite.setTexture(texture);
    if (textureRect != sf::IntRect()) {
        sprite.setTextureRect(textureRect);
    }
 //   sprite.setTextureRect(textureRect);
    sprite.setScale(0.07f, 0.07f);
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

}

void Missile::update() {
    adjustDirection(); 
    position += direction * speed;
    sprite.setPosition(position);
    // 방향 벡터를 기반으로 회전 각도 계산
    float angleDegrees = atan2(direction.y, direction.x) * 180.0f / 3.14159265f+90.0f;
    sprite.setRotation(angleDegrees);

   // shape.setPosition(position);
}

void Missile::draw(sf::RenderWindow& window) { 
    window.draw(sprite);
}
