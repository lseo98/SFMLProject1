#pragma once
#include "PlayerAttack.h"
#include "Projectile.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

class LandPlayerAttack : public PlayerAttack {
public:
    LandPlayerAttack();

    void basic_attack(const sf::Vector2f& playerPosition) override;
    void special_attack(const sf::Vector2f& playerPosition) override;
    void ultimate_attack() override;
    void updateProjectiles();
    void drawProjectiles(sf::RenderWindow& window);
    void handleInput(); // 방향 전환을 위한 입력 처리 메서드

private:
    std::vector<std::unique_ptr<Projectile>> projectiles; // 발사체들을 저장하는 벡터
    sf::Vector2f bulletDirection; // 기본 공격 방향 (왼쪽 또는 오른쪽)
};
