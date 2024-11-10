#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include <vector>
#include <chrono> // �ð� ������ �ʿ��� ��� ����

class Stage {
public:
    Stage();
    void setStage(int stageNumber, Player& player, std::vector<Enemy*>& enemies);
    void spawnEnemies(std::vector<Enemy*>& enemies);
    void update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window);  // update �޼��� ����

private:
    int stageNumber;
    bool bossSpawned;
    std::chrono::steady_clock::time_point lastAttackTime; // ���� ������ ���� �ð� ����

    void setPlayerAttackStrategy(int stageNumber, Player& player);
    void setEnemyAttackPatterns(int stageNumber, std::vector<Enemy*>& enemies);
};
