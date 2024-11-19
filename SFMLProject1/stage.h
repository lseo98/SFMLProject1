#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include <vector>

class Stage {
public:
    Stage();
    void setStage(int stageNumber, Player& player, std::vector<Enemy*>& enemies);
    void spawnEnemies(std::vector<Enemy*>& enemies, float deltaTime);
    //void update(Player& player, float deltaTime);  // ��Ÿ Ÿ���� ����ϴ� update �޼���
    void drawBackground(sf::RenderWindow& window); // ����� �׸��� �Լ�

private:
    sf::RenderWindow* window;
    int stageNumber;
    bool bossSpawned;
    float timeSinceLastAttack = 0.0f; // ��Ÿ Ÿ�� ��� ���� ������ ���� ����
    float attackCooldown = 0.2f;      // ���� ������ 200ms�� ����

    void setPlayerAttack(int stageNumber, Player& player);
    void setEnemyAttack(int stageNumber, std::vector<Enemy*>& enemies);

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite1;
    float scrollSpeed;
    float backgroundYPos; // Y �� ��ũ�� ��ġ (�ϴ�)
    float backgroundXPos; // X �� ��ũ�� ��ġ (�ٴ�)

    // �� ���� ����
    sf::Clock enemySpawnClock; // �� ���� Ÿ�̸�
    float spawnInterval = 2.0f; // �� ���� ���� (��)
    size_t maxEnemies = 10;    // �ִ� �� �� ����
};
