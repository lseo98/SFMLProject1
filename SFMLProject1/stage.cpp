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

    // 스테이지 변경 시 적 초기화
    for (auto* enemy : enemies) {
        delete enemy; // 기존 적 삭제
    }
    enemies.clear(); // 벡터 초기화

    // 배경 뷰 설정
    sf::FloatRect viewRect(450, 0, 900, 900); // 크기: 900x900
    backgroundView.reset(viewRect);

    // Viewport 설정
    backgroundView.setViewport(sf::FloatRect(
        450.f / 1800.f, // 상대 x 위치
        0.f,            // 상대 y 위치
        900.f / 1800.f, // 상대 너비
        1.f             // 상대 높이
    ));

    // 배경 설정
    if (stageNumber == 1) {
        backgroundTexture.loadFromFile("sky.png");

        scrollSpeed = 1.0f;
        backgroundYPos = 0;
    }
    else if (stageNumber == 2) {
        backgroundTexture.loadFromFile("sea.png");

        scrollSpeed = 0.7f;
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
    // 기존 뷰 저장
    sf::View originalView = window.getView();

    // 배경 뷰 설정
    window.setView(backgroundView);
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
        if (backgroundXPos <= -450) {
            backgroundXPos = 450;  // 스크롤 위치 초기화
        }
        backgroundSprite.setPosition(backgroundXPos, 0);
        backgroundSprite1.setPosition(backgroundXPos + 900, 0);
    }

    // 창의 지정된 영역(450~1350) 내에만 배경 출력
    window.draw(backgroundSprite);
    window.draw(backgroundSprite1);
    window.setView(originalView);

}

void Stage::spawnEnemies(std::vector<Enemy*>& enemies, float deltaTime) {
    // 시간 누적
    timeSinceLastAttack += deltaTime;

    // 적 생성 주기
    if (timeSinceLastAttack >= spawnInterval && enemies.size() < maxEnemies) {
        float normalUnitStartX = 0, normalUnitStartY = 0;
        float eliteUnitStartX = 0, eliteUnitStartY = 0;

        if (stageNumber == 1) { // 하늘 스테이지: 맨 위에서 랜덤 X 위치
            normalUnitStartX = rand() % (1350 - 450) + 450; // 일반 유닛 X 좌표: 화면의 중앙 영역
            normalUnitStartY = -50;                           // 일반 유닛 Y 좌표: 화면 상단

            eliteUnitStartX = rand() % (1350 - 450) + 450;  // 정예 유닛 X 좌표: 화면의 중앙 영역
            eliteUnitStartY = -50;                            // 정예 유닛 Y 좌표: 화면 상단
        }
        else if (stageNumber == 2) { // 바다 스테이지: 맨 오른쪽에서 랜덤 Y 위치
            normalUnitStartX = 1400;                        // 일반 유닛 X 좌표: 화면 오른쪽 끝
            normalUnitStartY = rand() % 900;                // 일반 유닛 Y 좌표: 화면 전체 높이

            eliteUnitStartX = 1400;                         // 정예 유닛 X 좌표: 화면 오른쪽 끝
            eliteUnitStartY = rand() % 900;                 // 정예 유닛 Y 좌표: 화면 전체 높이
        }
        else if (stageNumber == 3) { // 땅 스테이지: 양 옆 맨 아래
            if (rand() % 2 == 0) {
                normalUnitStartX = 400; // 일반 유닛 왼쪽 시작
            }
            else {
                normalUnitStartX = 1400; // 일반 유닛 오른쪽 시작
            }
            normalUnitStartY = 700; // 일반 유닛 Y 좌표: 화면 아래

            if (rand() % 2 == 0) {
                eliteUnitStartX = 400; // 정예 유닛 왼쪽 시작
            }
            else {
                eliteUnitStartX = 1400; // 정예 유닛 오른쪽 시작
            }
            eliteUnitStartY = 200; // 정예 유닛 Y 좌표: 화면 위
        }

        // 일반 유닛 생성
        NormalUnit* normalUnit = new NormalUnit(stageNumber, sf::Vector2f(normalUnitStartX, normalUnitStartY));
        if (stageNumber == 3) {
            int direction = (normalUnitStartX == 400) ? 1 : -1; // 왼쪽에서 시작하면 오른쪽으로, 오른쪽에서 시작하면 왼쪽으로
            normalUnit->updateDirection(direction);
        }
        enemies.push_back(normalUnit);

        // 정예 유닛 생성
        EliteUnit* eliteUnit = new EliteUnit(stageNumber, sf::Vector2f(eliteUnitStartX, eliteUnitStartY));
        if (stageNumber == 3) {
            int direction = (eliteUnitStartX == 400) ? 1 : -1; // 왼쪽에서 시작하면 오른쪽으로, 오른쪽에서 시작하면 왼쪽으로
            eliteUnit->updateDirection(direction);
        }
        //eliteUnit->initializeRandomSpeeds(); // 정예 유닛의 랜덤 속도 초기화
        enemies.push_back(eliteUnit);

        // 타이머 초기화
        timeSinceLastAttack = 0.0f;
    }
}



void Stage::setPlayerAttack(int stageNumber, Player& player) {
    if (stageNumber == 1) {
        player.image("sky_my_unit.PNG");
        player.setPlayerAttack(std::make_unique<SkyPlayerAttack>());
    }
    else if (stageNumber == 2) {
        player.image("sea_my_unit_right.png");
        player.setPlayerAttack(std::make_unique<SeaPlayerAttack>());
    }
    else if (stageNumber == 3) {
        player.image("land_my_unit_right.png");
        player.setPlayerAttack(std::make_unique<LandPlayerAttack>());
    }
}

void Stage::setEnemyAttack(int stageNumber, std::vector<Enemy*>& enemies) {
    for (auto* enemy : enemies) {
        AttackType type = dynamic_cast<NormalUnit*>(enemy) ? AttackType::Normal : AttackType::Elite;
        std::unique_ptr<EnemyAttack> attackPattern;
        if (stageNumber == 1) {
            attackPattern = std::make_unique<SkyEnemyAttack>(type);
            //if (type == AttackType::Normal) {
            //    enemy->image("sky_enemy_unit.png");   // 이미지 설정
            //}
            //else {
            //    enemy->image("sky_elite_unit.png");
            //}
        }
        else if (stageNumber == 2) {
            attackPattern = std::make_unique<SeaEnemyAttack>(type);
            //if (type == AttackType::Normal) {
            //    enemy->image("sea_enemy_unit.png");   // 이미지 설정
            //}
            //else {
            //    enemy->image("sea_elite_unit.png");
            //}
        }
        else if (stageNumber == 3) {
            attackPattern = std::make_unique<LandEnemyAttack>(type);
            //if (type == AttackType::Normal) {
            //    enemy->image("land_enemy_unit.png");   // 이미지 설정
            //}
            //else {
            //    enemy->image("land_elite_unit.png");
            //}
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