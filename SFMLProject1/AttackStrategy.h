#pragma once
#include <SFML/Graphics.hpp>

class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;

    virtual void basic_attack(const sf::Vector2f& playerPosition) = 0; // ��ġ ���� �߰�
    virtual void special_attack(const sf::Vector2f& playerPosition) = 0; // ��ġ ���� �߰�
    virtual void ultimate_attack() = 0;

    virtual void updateProjectiles(sf::RenderWindow& window) = 0;
};
