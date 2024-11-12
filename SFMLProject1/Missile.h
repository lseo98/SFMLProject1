#pragma once
#include "Projectile.h"

class Missile : public Projectile {
public:
    Missile(const sf::Vector2f& startPosition);

    void update() override;
    void draw(sf::RenderWindow& window) override;
};
