#include "Stage.h"
#include "SkyAttackStrategy.h"
#include "SeaAttackStrategy.h"
#include "LandAttackStrategy.h"
#include "SkyNormalAttack.h"
#include "SkyEliteAttack.h"
#include "SeaNormalAttack.h"
#include "SeaEliteAttack.h"
#include "LandNormalAttack.h"
#include "LandEliteAttack.h"
#include <memory>
#include <chrono>

Stage::Stage() : stageNumber(1), bossSpawned(false), lastAttackTime(std::chrono::steady_clock::now()) { }

void Stage::setStage(int stageNumber, Player& player, std::vector<Enemy*>& enemies) {
    this->stageNumber = stageNumber;
    // 배경 설정
    if (stageNumber == 1) {
        backgroundTexture.loadFromFile("sky.png");
        scrollSpeed = 1.0f;
        backgroundYPos = 0;
    }
    else if (stageNumber == 2) {
        backgroundTexture.loadFromFile("sea.png");
        scrollSpeed = 1.0f;
        backgroundXPos = 0;
    }
    else if (stageNumber == 3) {
        backgroundTexture.loadFromFile("land.png");
        scrollSpeed = 0.0f;  // 땅 스테이지는 정지된 배경
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite1.setTexture(backgroundTexture);

    backgroundSprite.setPosition(450, 0);  // 화면 중앙 영역에 배경 설정
    backgroundSprite1.setPosition(450, -(float)backgroundTexture.getSize().y);
    setPlayerAttackStrategy(stageNumber, player);
    setEnemyAttackPatterns(stageNumber, enemies);
}
void Stage::drawBackground(sf::RenderWindow& window) {
    if (stageNumber == 1) { // 하늘 스테이지: 위로 스크롤
        backgroundYPos += scrollSpeed;
        if (backgroundYPos >= backgroundTexture.getSize().y) {
            backgroundYPos = 0;  // 스크롤 위치 초기화
        }
        backgroundSprite.setPosition(450, backgroundYPos);
        backgroundSprite1.setPosition(450, backgroundYPos - backgroundTexture.getSize().y);
    }
    else if (stageNumber == 2) { // 바다 스테이지: 옆으로 스크롤
        backgroundXPos += scrollSpeed;
        if (backgroundXPos >= backgroundTexture.getSize().x) {
            backgroundXPos = 450;  // 스크롤 위치 초기화
        }
        backgroundSprite.setPosition(450 + backgroundXPos, 0);
        backgroundSprite1.setPosition(450 + backgroundXPos - backgroundTexture.getSize().x, 0);
    }

    // 창의 지정된 영역(450~1350) 내에만 배경 출력
    window.draw(backgroundSprite);
    window.draw(backgroundSprite1);
}


void Stage::spawnEnemies(std::vector<Enemy*>& enemies) {
    // 기존 적 유닛 삭제
    for (auto* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    // 스테이지 번호에 따라 적 유닛 생성
    if (stageNumber == 1) {  // 하늘 스테이지
        enemies.push_back(new NormalUnit());
        enemies.back()->image("sky_enemy_unit.png");   // 이미지 파일 지정
        enemies.push_back(new EliteUnit());
        enemies.back()->image("sky_elite_unit.png");
    }
    else if (stageNumber == 2) {  // 바다 스테이지
        enemies.push_back(new NormalUnit());
        enemies.back()->image("sea_enemy_unit.png");
        enemies.push_back(new EliteUnit());
        enemies.back()->image("sea_elite_unit.png");
    }
    else if (stageNumber == 3) {  // 땅 스테이지
        enemies.push_back(new NormalUnit());
        enemies.back()->image("land_enemy_unit.png");
        enemies.push_back(new EliteUnit());
        enemies.back()->image("land_elite_unit.png");
    }
    // 땅 스테이지에서 보스 등장
    if (stageNumber == 3 && !bossSpawned) {
        enemies.push_back(new Boss());
        bossSpawned = true;
    }
}



void Stage::setPlayerAttackStrategy(int stageNumber, Player& player) {
    if (stageNumber == 1) {
        player.image("sky_my_unit.PNG");
        player.setAttackStrategy(std::make_unique<SkyAttackStrategy>());
    }
    else if (stageNumber == 2) {
        player.image("sea_my_unit.png");
        player.setAttackStrategy(std::make_unique<SeaAttackStrategy>());
    }
    else if (stageNumber == 3) {
        player.image("land_my_unit_left.png");
        player.setAttackStrategy(std::make_unique<LandAttackStrategy>());
    }
}

void Stage::setEnemyAttackPatterns(int stageNumber, std::vector<Enemy*>& enemies) {
    for (auto* enemy : enemies) {
        if (auto* normalUnit = dynamic_cast<NormalUnit*>(enemy)) {
            if (stageNumber == 1) {
                normalUnit->image("sky_enemy_unit.png");
                normalUnit->setAttackPattern(std::make_unique<SkyNormalAttack>());
            }
            else if (stageNumber == 2) {
                normalUnit->image("sea_enemy_unit.png");
                normalUnit->setAttackPattern(std::make_unique<SeaNormalAttack>());
            }
            else if (stageNumber == 3) {
                normalUnit->image("land_enemy_unit.png");
                normalUnit->setAttackPattern(std::make_unique<LandNormalAttack>());
            }
        }
        else if (auto* eliteUnit = dynamic_cast<EliteUnit*>(enemy)) {
            if (stageNumber == 1) {
                eliteUnit->image("sky_elite_unit.png");
                eliteUnit->setAttackPattern(std::make_unique<SkyEliteAttack>());
            }
            else if (stageNumber == 2) {
                eliteUnit->image("sea_elite_unit.png");
                eliteUnit->setAttackPattern(std::make_unique<SeaEliteAttack>());
            }
            else if (stageNumber == 3) {
                eliteUnit->image("land_elite_unit.png");
                eliteUnit->setAttackPattern(std::make_unique<LandEliteAttack>());
            }
        }
    }
}

// update 메서드: 플레이어의 기본 공격을 200ms 간격으로 자동 실행하고 발사체 및 적을 업데이트
void Stage::update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window) {
    // 200ms마다 기본 공격 수행
    drawBackground(window);

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAttackTime).count() > 200) { 
        player.performBasicAttack(); // 기본 공격 수행
        lastAttackTime = now;
    } 
}





