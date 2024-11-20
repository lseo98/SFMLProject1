#pragma once
#include "Projectile.h"

class Bullet : public Projectile {
public:
    Bullet(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed);

    void update() override;
    void draw(sf::RenderWindow& window) override;
};
