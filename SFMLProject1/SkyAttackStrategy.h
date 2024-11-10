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
    void updateProjectiles(sf::RenderWindow& window); // �߻�ü ������Ʈ �޼���

private:
    std::vector<std::unique_ptr<Projectile>> projectiles; // �߻�ü���� �����ϴ� ����
};
