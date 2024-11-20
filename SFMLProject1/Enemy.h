#pragma once
#include "Character.h"
#include "EnemyAttack.h"
#include <memory>
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position, int stageNumber);

    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window) override;

    virtual void attack() = 0;
    virtual void update(float deltaTime); // 이동 업데이트 추가
    void setEnemyAttack(std::unique_ptr<EnemyAttack> attackPattern);

    void image(const std::string& textureFile);

    void updateDirection(int newDirection = 0); // 방향 가져오기 

    bool isOffScreen() const; // 중앙 900x900 범위를 기준으로 화면 밖으로 나갔는지 확인

    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트

protected:
    int stageNumber;  // 스테이지 번호
    int direction;    // 땅 스테이지에서만 사용되는 방향 (1: 오른쪽, -1: 왼쪽)

    float targetX = 0.0f; // 목표 X 좌표
    float targetY = 0.0f; // 목표 Y 좌표
    float nextTargetY = 0.0f; // 하늘 스테이지: 다음 Y 목표값
    float nextTargetX = 1350.0f; // 바다 스테이지: 다음 X 목표값

    std::unique_ptr<EnemyAttack> attackPattern;
};

class NormalUnit : public Enemy {
public:
    NormalUnit(int stageNumber, sf::Vector2f position)
        : Enemy(100.0f, 1.0f, position, stageNumber) {
        image(stageNumber == 1 ? "sky_enemy_unit.png" :
              stageNumber == 2 ? "sea_enemy_unit_b.png" :
                                 "land_enemy_unit.png"); // 이미지 설정
    }

    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }
};

class EliteUnit : public Enemy {
public:
    EliteUnit(int stageNumber, sf::Vector2f position)
        : Enemy(300.0f, 1.5f, position, stageNumber) {
        image(stageNumber == 1 ? "sky_elite_unit.png" :
              stageNumber == 2 ? "sea_elite_unit.png" :
                                 "land_elite_unit.png"); // 이미지 설정
    }

    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }

};
