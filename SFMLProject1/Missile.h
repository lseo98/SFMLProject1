#pragma once
#include "Projectile.h"

class Missile : public Projectile {
public:
    Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed);

    void update() override;
    void draw(sf::RenderWindow& window) override;
    float getRange() { return range; }


    sf::CircleShape shape;   // SFML에서 사용할 기본 도형 (예: 원형 모양)

private:
    float range;
};
