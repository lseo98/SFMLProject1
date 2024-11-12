#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>

class AntiTankMissile : public Projectile {
public:
    AntiTankMissile(const sf::Vector2f& startPosition);

    void update() override;
    void draw(sf::RenderWindow& window) override;
};
