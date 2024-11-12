//#include "Stage.h"
//#include "SkyAttackStrategy.h"
//#include "SeaAttackStrategy.h"
//#include "LandAttackStrategy.h"
//#include "SkyNormalAttack.h"
//#include "SkyEliteAttack.h"
//#include "SeaNormalAttack.h"
//#include "SeaEliteAttack.h"
//#include "LandNormalAttack.h"
//#include "LandEliteAttack.h"
//#include <memory>
//#include <chrono>
//
//Stage::Stage() : stageNumber(1), bossSpawned(false), lastAttackTime(std::chrono::steady_clock::now()) { }
//
//void Stage::setStage(int stageNumber, Player& player, std::vector<Enemy*>& enemies) {    
//    this->stageNumber = stageNumber;
//
//    setPlayerAttackStrategy(stageNumber, player);
//    setEnemyAttackPatterns(stageNumber, enemies);
//}
//
//void Stage::spawnEnemies(std::vector<Enemy*>& enemies) { 
//    enemies.clear(); // 스테이지 변경 시 기존 적 삭제
//
//    enemies.push_back(new NormalUnit());
//    enemies.push_back(new EliteUnit());
//
//    // 땅 스테이지에서 보스 등장
//    if (stageNumber == 3 && !bossSpawned) {
//        enemies.push_back(new Boss());
//        bossSpawned = true;
//    }
//}
//
//void Stage::setPlayerAttackStrategy(int stageNumber, Player& player) {
//    if (stageNumber == 1) {
//        player.setAttackStrategy(std::make_unique<SkyAttackStrategy>());
//    }
//    else if (stageNumber == 2) {
//        player.setAttackStrategy(std::make_unique<SeaAttackStrategy>());
//    }
//    else if (stageNumber == 3) {
//        player.setAttackStrategy(std::make_unique<LandAttackStrategy>());
//    }
//}
//
//void Stage::setEnemyAttackPatterns(int stageNumber, std::vector<Enemy*>& enemies) {
//    for (auto* enemy : enemies) {
//        if (auto* normalUnit = dynamic_cast<NormalUnit*>(enemy)) {
//            if (stageNumber == 1) {
//                normalUnit->setAttackPattern(std::make_unique<SkyNormalAttack>());
//            }
//            else if (stageNumber == 2) {
//                normalUnit->setAttackPattern(std::make_unique<SeaNormalAttack>());
//            }
//            else if (stageNumber == 3) {
//                normalUnit->setAttackPattern(std::make_unique<LandNormalAttack>());
//            }
//        }
//        else if (auto* eliteUnit = dynamic_cast<EliteUnit*>(enemy)) {
//            if (stageNumber == 1) {
//                eliteUnit->setAttackPattern(std::make_unique<SkyEliteAttack>());
//            }
//            else if (stageNumber == 2) {
//                eliteUnit->setAttackPattern(std::make_unique<SeaEliteAttack>());
//            }
//            else if (stageNumber == 3) {
//                eliteUnit->setAttackPattern(std::make_unique<LandEliteAttack>());
//            }
//        }
//    }
//}
//
//// update 메서드: 플레이어의 기본 공격을 200ms 간격으로 자동 실행하고 발사체 및 적을 업데이트
//void Stage::update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window) {
//    // 200ms마다 기본 공격 수행
//    auto now = std::chrono::steady_clock::now();
//    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAttackTime).count() > 200) {
//        player.performBasicAttack(); // 기본 공격 수행
//        lastAttackTime = now;
//    }
//
//
//}


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
    bossSpawned = false;  // 보스가 다시 스폰될 수 있도록 초기화
    setPlayerAttackStrategy(stageNumber, player);
    spawnEnemies(enemies);  // 스테이지에 맞는 적 유닛을 스폰
    player.setStage(stageNumber); // Player 클래스에 스테이지 번호 전달

}

void Stage::spawnEnemies(std::vector<Enemy*>& enemies) {
    // 기존 적 유닛 삭제
    for (auto* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

        // 땅 스테이지에서 보스 등장
    if (stageNumber == 3 && !bossSpawned) {
        enemies.push_back(new Boss());
        bossSpawned = true;
    }

    setEnemyAttackPatterns(stageNumber, enemies);  // 스테이지에 맞는 공격 패턴 설정
}

void Stage::setPlayerAttackStrategy(int stageNumber, Player& player) {
    if (stageNumber == 1) {
        player.setAttackStrategy(std::make_unique<SkyAttackStrategy>());
    }
    else if (stageNumber == 2) {
        player.setAttackStrategy(std::make_unique<SeaAttackStrategy>());
    }
    else if (stageNumber == 3) {
        player.setAttackStrategy(std::make_unique<LandAttackStrategy>());
    }
}

void Stage::setEnemyAttackPatterns(int stageNumber, std::vector<Enemy*>& enemies) {
    for (auto* enemy : enemies) {
        if (auto* normalUnit = dynamic_cast<NormalUnit*>(enemy)) {
            if (stageNumber == 1) {
                normalUnit->setAttackPattern(std::make_unique<SkyNormalAttack>());
            }
            else if (stageNumber == 2) {
                normalUnit->setAttackPattern(std::make_unique<SeaNormalAttack>());
            }
            else if (stageNumber == 3) {
                normalUnit->setAttackPattern(std::make_unique<LandNormalAttack>());
            }
        }
        else if (auto* eliteUnit = dynamic_cast<EliteUnit*>(enemy)) {
            if (stageNumber == 1) {
                eliteUnit->setAttackPattern(std::make_unique<SkyEliteAttack>());
            }
            else if (stageNumber == 2) {
                eliteUnit->setAttackPattern(std::make_unique<SeaEliteAttack>());
            }
            else if (stageNumber == 3) {
                eliteUnit->setAttackPattern(std::make_unique<LandEliteAttack>());
            }
        }
    }
}

// update 메서드: 플레이어의 기본 공격을 200ms 간격으로 자동 실행하고 발사체 및 적을 업데이트
void Stage::update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window) {
    // 200ms마다 기본 공격 수행
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAttackTime).count() > 200) {
        player.performBasicAttack();  // 기본 공격 수행
        lastAttackTime = now;
    }

    // 모든 적의 공격 패턴 업데이트 및 화면에 그리기
    for (auto* enemy : enemies) {
        enemy->attack();     // 적의 공격 수행
        enemy->draw(window); // 적을 화면에 그리기
    }
}
