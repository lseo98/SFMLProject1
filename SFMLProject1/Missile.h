#pragma once
#include "Projectile.h"

class Missile : public Projectile {
public:
    Missile(const sf::Vector2f& startPosition);

    void update() override;
    void draw(sf::RenderWindow& window) override;
    bool isOffScreen(int screenWidth, int screenHeight) const override; // 오버라이딩
};
