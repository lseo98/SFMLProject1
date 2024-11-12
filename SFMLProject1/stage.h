#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include <vector>

class Stage {
public:
    Stage();
    void setStage(int stageNumber, Player& player, std::vector<Enemy*>& enemies);
    void spawnEnemies(std::vector<Enemy*>& enemies);
    //void update(Player& player, float deltaTime);  // ��Ÿ Ÿ���� ����ϴ� update �޼���

private:
    int stageNumber;
    bool bossSpawned;
    float timeSinceLastAttack = 0.0f; // ��Ÿ Ÿ�� ��� ���� ������ ���� ����
    float attackCooldown = 0.2f;      // ���� ������ 200ms�� ����

    void setPlayerAttack(int stageNumber, Player& player);
    void setEnemyAttack(int stageNumber, std::vector<Enemy*>& enemies);
};
