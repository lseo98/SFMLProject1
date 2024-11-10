#pragma once
#include "AttackStrategy.h"
#include "Projectile.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

class SkyAttackStrategy : public AttackStrategy {
public:
    SkyAttackStrategy() = default;

    void basic_attack(const sf::Vector2f& playerPosition) override;
    void special_attack(const sf::Vector2f& playerPosition) override;
    void ultimate_attack() override;
    void updateProjectiles(sf::RenderWindow& window); // 발사체 업데이트 메서드

private:
    std::vector<std::unique_ptr<Projectile>> projectiles; // 발사체들을 저장하는 벡터
};
