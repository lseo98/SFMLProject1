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
    void drawBackground(sf::RenderWindow& window); // 배경을 그리는 함수

private:
    sf::RenderWindow* window;
    int stageNumber;
    bool bossSpawned;
    float normalTimeSinceLastAttack = 0.0f; // 델타 타임 기반 공격 간격을 위한 변수
    float eliteTimeSinceLastAttack = 0.0f; // 델타 타임 기반 공격 간격을 위한 변수
    float attackCooldown = 0.2f;      // 공격 간격을 200ms로 설정
    int direction;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite1;
    sf::View backgroundView; // 배경 뷰

    float scrollSpeed;
    float backgroundYPos; // Y 축 스크롤 위치 (하늘)
    float backgroundXPos; // X 축 스크롤 위치 (바다)

    // 적 생성 관리
    sf::Clock enemySpawnClock; // 적 생성 타이머
    float normalSpawnInterval = 2.0f; // 일반 유닛 생성 간격 (초)
    float eliteSpawnInterval = 4.0f; // 정예 유닛 생성 간격 (초)
    size_t maxEnemies = 20;    // 최대 적 수 제한
};
