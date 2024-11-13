#pragma once
#include "Character.h"
#include "EnemyAttack.h"
#include <memory>
#include <iostream>

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position);

    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window) override;

    virtual void attack() = 0;
    void setEnemyAttack(std::unique_ptr<EnemyAttack> attackPattern);

    void image(const std::string& textureFile);


    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트

protected:
    std::unique_ptr<EnemyAttack> attackPattern;
};

class NormalUnit : public Enemy {
public:
    NormalUnit() : Enemy(100.0f, 1.0f, sf::Vector2f(0,0)) {
        image("sky_enemy_unit.png");  // 이미지 파일을 초기화
    }
    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }
};

class EliteUnit : public Enemy {
public:
    EliteUnit() : Enemy(300.0f, 1.5f, sf::Vector2f(0, 0)) {
        image("sky_elite_unit.png");  // 이미지 파일을 초기화
    }
    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }
};
