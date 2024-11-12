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
    void handleInput(); // ���� ��ȯ�� ���� �Է� ó�� �޼���

private:
    std::vector<std::unique_ptr<Projectile>> projectiles; // �߻�ü���� �����ϴ� ����
    sf::Vector2f bulletDirection; // �⺻ ���� ���� (���� �Ǵ� ������)
};
