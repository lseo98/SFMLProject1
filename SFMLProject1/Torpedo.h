#pragma once
#include "Projectile.h"

class Torpedo : public Projectile {
public:
    Torpedo(const sf::Vector2f& startPosition);

    void update() override;
    void draw(sf::RenderWindow& window) override;
};
