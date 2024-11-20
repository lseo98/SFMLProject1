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
    virtual void update(float deltaTime); // �̵� ������Ʈ �߰�
    void setEnemyAttack(std::unique_ptr<EnemyAttack> attackPattern);

    void image(const std::string& textureFile);

    void updateDirection(int newDirection = 0); // ���� �������� 

    bool isOffScreen() const; // �߾� 900x900 ������ �������� ȭ�� ������ �������� Ȯ��

    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ

protected:
    int stageNumber;  // �������� ��ȣ
    int direction;    // �� �������������� ���Ǵ� ���� (1: ������, -1: ����)

    float targetX = 0.0f; // ��ǥ X ��ǥ
    float targetY = 0.0f; // ��ǥ Y ��ǥ
    float nextTargetY = 0.0f; // �ϴ� ��������: ���� Y ��ǥ��
    float nextTargetX = 1350.0f; // �ٴ� ��������: ���� X ��ǥ��

    std::unique_ptr<EnemyAttack> attackPattern;
};

class NormalUnit : public Enemy {
public:
    NormalUnit(int stageNumber, sf::Vector2f position)
        : Enemy(100.0f, 1.0f, position, stageNumber) {
        image(stageNumber == 1 ? "sky_enemy_unit.png" :
              stageNumber == 2 ? "sea_enemy_unit_b.png" :
                                 "land_enemy_unit.png"); // �̹��� ����
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
                                 "land_elite_unit.png"); // �̹��� ����
    }

    void attack() override {
        if (attackPattern) attackPattern->attack_pattern();
    }

};
