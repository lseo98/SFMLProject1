#pragma once
#include "Projectile.h"

class Missile : public Projectile {
public:
    Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed);

    void update() override;
    void update(const sf::Vector2f& targetPosition); // 추적 미사일 업데이트

    void draw(sf::RenderWindow& window) override;
    float getRange() { return range; }

    void setTexture(const sf::Texture& texture, const sf::IntRect& textureRect);
    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;

    void changeRange(float range) { this->range = range; }

    void setTarget();


private:
    float range;
    sf::Vector2f* targetPosition = nullptr; // 플레이어 위치 참조
    bool isTracking = false;                // 추적 여부
};
