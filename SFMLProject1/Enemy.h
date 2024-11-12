#pragma once
#include "Character.h"
#include "EnemyAttackPattern.h"
#include <memory>
#include <iostream>

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position, const std::string& textureFile);

    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window) override;

    virtual void attack() = 0;
    void setAttackPattern(std::unique_ptr<EnemyAttackPattern> attackPattern);  

    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트

protected:
    std::unique_ptr<EnemyAttackPattern> attackPattern;
};

class NormalUnit : public Enemy {
public:
    NormalUnit(int stageNumber) : Enemy(100.0f, 1.0f, sf::Vector2f(0, 0), getTextureFile(stageNumber)) {}
    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }
    static std::string getTextureFile(int stageNumber) {
        switch (stageNumber) {
        case 1: return "sky_enemy_unit.png";
        case 2: return "sea_enemy_unit.png";
        case 3: return "land_enemy_unit.png";  
        }
    }
};

class EliteUnit : public Enemy {
public:
    EliteUnit(int stageNumber) : Enemy(300.0f, 1.5f, sf::Vector2f(0, 0), getTextureFile(stageNumber)) {}

    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }

    static std::string getTextureFile(int stageNumber) {
        switch (stageNumber) {
        case 1: return "sky_elite_unit.png";
        case 2: return "sea_elite_unit.png";
        case 3: return "land_elite_unit.png";
        }
    }
};
