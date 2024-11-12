#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include <vector>
#include <chrono> // 시간 관리에 필요한 헤더 파일

class Stage {
public:
    Stage();
    void setStage(int stageNumber, Player& player, std::vector<Enemy*>& enemies);
    void spawnEnemies(std::vector<Enemy*>& enemies);
    void update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window);  // update 메서드 선언
    void drawBackground(sf::RenderWindow& window); // 배경을 그리는 함수

private:
    sf::RenderWindow* window;
    int stageNumber;
    bool bossSpawned;
    std::chrono::steady_clock::time_point lastAttackTime; // 공격 간격을 위한 시간 변수

    void setPlayerAttackStrategy(int stageNumber, Player& player);
    void setEnemyAttackPatterns(int stageNumber, std::vector<Enemy*>& enemies);
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite1;
    float scrollSpeed;
    float backgroundYPos; // Y 축 스크롤 위치 (하늘)
    float backgroundXPos; // X 축 스크롤 위치 (바다)
};
