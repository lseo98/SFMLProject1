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

private:
    int stageNumber;
    bool bossSpawned;

    void setPlayerAttackStrategy(int stageNumber, Player& player);
    void setEnemyAttackPatterns(int stageNumber, std::vector<Enemy*>& enemies);
};
