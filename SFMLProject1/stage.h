#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include <vector>

class Stage {
public:
    Stage();

    void setStage(int stageNumber, std::vector<Enemy*>& enemies);
    void spawnEnemies(std::vector<Enemy*>& enemies, float deltaTime);
    void drawBackground(sf::RenderWindow& window); // ����� �׸��� �Լ�

private:
    sf::RenderWindow* window;
    int stageNumber;
    bool bossSpawned;
    float normalTimeSinceLastAttack = 0.0f; // ��Ÿ Ÿ�� ��� ���� ������ ���� ����
    float eliteTimeSinceLastAttack = 0.0f; // ��Ÿ Ÿ�� ��� ���� ������ ���� ����
    float attackCooldown = 0.2f;      // ���� ������ 200ms�� ����
    int direction;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite1;
    sf::View backgroundView; // ��� ��

    float scrollSpeed;
    float backgroundYPos; // Y �� ��ũ�� ��ġ (�ϴ�)
    float backgroundXPos; // X �� ��ũ�� ��ġ (�ٴ�)

    // �� ���� ����
    sf::Clock enemySpawnClock; // �� ���� Ÿ�̸�
    float normalSpawnInterval = 2.0f; // �Ϲ� ���� ���� ���� (��)
    float eliteSpawnInterval = 4.0f; // ���� ���� ���� ���� (��)
    size_t maxEnemies = 20;    // �ִ� �� �� ����
};
