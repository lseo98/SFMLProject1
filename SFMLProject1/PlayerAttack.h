#pragma once
#include <SFML/Graphics.hpp>

class PlayerAttack {
public:
    virtual ~PlayerAttack() = default;

    virtual void basic_attack(const sf::Vector2f& playerPosition) = 0; // 위치 인자 추가
    virtual void special_attack(const sf::Vector2f& playerPosition) = 0; // 위치 인자 추가
    virtual void ultimate_attack() = 0;

    virtual void updateProjectiles() = 0;      // 발사체 업데이트
    virtual void drawProjectiles(sf::RenderWindow& window) = 0; // 발사체 그리기
};
