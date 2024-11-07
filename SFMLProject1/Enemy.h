#pragma once
#include "Character.h"
#include "EnemyAttackPattern.h"
#include <memory>
#include <iostream>

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position);

    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window) override;

    virtual void attack() = 0;
    void setAttackPattern(std::unique_ptr<EnemyAttackPattern> attackPattern);

protected:
    std::unique_ptr<EnemyAttackPattern> attackPattern;
};

class NormalUnit : public Enemy {
public:
    NormalUnit() : Enemy(100.0f, 1.0f, sf::Vector2f(0,0)) {}
    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }
};

class EliteUnit : public Enemy {
public:
    EliteUnit() : Enemy(300.0f, 1.5f, sf::Vector2f(0, 0)) {}
    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }
};
