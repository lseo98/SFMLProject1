#pragma once
#include "Projectile.h"

class Bullet : public Projectile {
public:
    Bullet(const sf::Vector2f& startPosition, const sf::Vector2f& direction);

    void update() override;
    void draw(sf::RenderWindow& window) override;
    bool isOffScreen(int screenWidth, int screenHeight) const override;
};
