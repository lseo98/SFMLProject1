#pragma once
#include "Projectile.h"

class Bullet : public Projectile {
public:
    Bullet(const sf::Vector2f startPosition, const sf::Vector2f direction, float speed);

    void update() override;
    void draw(sf::RenderWindow& window) override;

    sf::CircleShape shape;   // SFML에서 사용할 기본 도형 (예: 원형 모양)
    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;
    void setTexture(const sf::Texture& texture, const sf::IntRect& textureRect);

};