#include "Stage.h"
#include "SkyPlayerAttack.h"
#include "SeaPlayerAttack.h"
#include "LandPlayerAttack.h"
#include "SkyEnemyAttack.h"
#include "SeaEnemyAttack.h"
#include "LandEnemyAttack.h"
#include <memory>

Stage::Stage() : stageNumber(1), bossSpawned(false), timeSinceLastAttack(0.0f), attackCooldown(0.2f) { }

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

    setPlayerAttack(stageNumber, player);
    setEnemyAttack(stageNumber, enemies);
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
        backgroundXPos -= scrollSpeed;
        if (backgroundXPos >= backgroundTexture.getSize().x) {
            backgroundXPos = 450;  // 스크롤 위치 초기화
        }
        backgroundSprite.setPosition(450 + backgroundXPos, 0);
        backgroundSprite1.setPosition(450 + backgroundXPos + backgroundTexture.getSize().x, 0);
    }

    // 창의 지정된 영역(450~1350) 내에만 배경 출력
    window.draw(backgroundSprite);
    window.draw(backgroundSprite1);
}

void Stage::spawnEnemies(std::vector<Enemy*>& enemies) {
    enemies.clear(); // 스테이지 변경 시 기존 적 삭제

    enemies.push_back(new NormalUnit());
    enemies.push_back(new EliteUnit());

    // 땅 스테이지에서 보스 등장
    if (stageNumber == 3 && !bossSpawned) {
        enemies.push_back(new Boss());
        bossSpawned = true;
    }
}

void Stage::setPlayerAttack(int stageNumber, Player& player) {
    if (stageNumber == 1) {
        player.image("sky_my_unit.PNG");
        player.setPlayerAttack(std::make_unique<SkyPlayerAttack>());
    }
    else if (stageNumber == 2) {
        player.image("sea_my_unit.png");
        player.setPlayerAttack(std::make_unique<SeaPlayerAttack>());
    }
    else if (stageNumber == 3) {
        player.image("land_my_unit_left.png");
        player.setPlayerAttack(std::make_unique<LandPlayerAttack>());
    }
}

void Stage::setEnemyAttack(int stageNumber, std::vector<Enemy*>& enemies) {
    for (auto* enemy : enemies) {
        AttackType type = dynamic_cast<NormalUnit*>(enemy) ? AttackType::Normal : AttackType::Elite;
        std::unique_ptr<EnemyAttack> attackPattern;
        if (stageNumber == 1) {
            attackPattern = std::make_unique<SkyEnemyAttack>(type);
            if (type == AttackType::Normal) {
                enemy->image("sky_enemy_unit.png");   // 이미지 설정
            }
            else {
                enemy->image("sky_elite_unit.png");
            }
        }
        else if (stageNumber == 2) {
            attackPattern = std::make_unique<SeaEnemyAttack>(type);
            if (type == AttackType::Normal) {
                enemy->image("sea_enemy_unit.png");   // 이미지 설정
            }
            else {
                enemy->image("sea_elite_unit.png");
            }
        }
        else if (stageNumber == 3) {
            attackPattern = std::make_unique<LandEnemyAttack>(type);
            if (type == AttackType::Normal) {
                enemy->image("land_enemy_unit.png");   // 이미지 설정
            }
            else {
                enemy->image("land_elite_unit.png");
            }
        }
        enemy->setEnemyAttack(std::move(attackPattern));
    }
}

//// update 메서드: 플레이어의 기본 공격을 200ms 간격으로 자동 실행
//void Stage::update(Player& player, float deltaTime) {
//    // 델타 타임을 누적하여 200ms마다 기본 공격 수행
//    timeSinceLastAttack += deltaTime;
//
//    if (timeSinceLastAttack >= 0.2f) { // 200ms 간격으로 공격
//        player.performBasicAttack();   // 기본 공격 수행
//        timeSinceLastAttack = 0.0f;    // 공격 간격 초기화
//    }
//}