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
    //void update(Player& player, float deltaTime);  // 델타 타임을 사용하는 update 메서드

private:
    int stageNumber;
    bool bossSpawned;
    float timeSinceLastAttack = 0.0f; // 델타 타임 기반 공격 간격을 위한 변수
    float attackCooldown = 0.2f;      // 공격 간격을 200ms로 설정

    void setPlayerAttack(int stageNumber, Player& player);
    void setEnemyAttack(int stageNumber, std::vector<Enemy*>& enemies);
};
