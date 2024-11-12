#pragma once
#include <SFML/Graphics.hpp>

class PlayerAttack {
public:
    virtual ~PlayerAttack() = default;

    virtual void basic_attack(const sf::Vector2f& playerPosition) = 0; // ��ġ ���� �߰�
    virtual void special_attack(const sf::Vector2f& playerPosition) = 0; // ��ġ ���� �߰�
    virtual void ultimate_attack() = 0;

    virtual void updateProjectiles() = 0;      // �߻�ü ������Ʈ
    virtual void drawProjectiles(sf::RenderWindow& window) = 0; // �߻�ü �׸���
};
