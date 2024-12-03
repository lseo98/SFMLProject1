#pragma once
#include "Projectile.h"

class Missile : public Projectile {
public:
    Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed);

    void update() override;
    void update(const sf::Vector2f& targetPosition); // 추적 미사일 업데이트

    void draw(sf::RenderWindow& window) override;
    float getRange() { return range; }
    void changeRange(float range) { this->range = range; }

    void setTarget();

    sf::CircleShape shape;   // SFML에서 사용할 기본 도형 (예: 원형 모양)

private:
    float range;
    sf::Vector2f* targetPosition = nullptr; // 플레이어 위치 참조
    bool isTracking = false;                // 추적 여부
};
