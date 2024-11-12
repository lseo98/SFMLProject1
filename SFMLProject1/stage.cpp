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
//    enemies.clear(); // �������� ���� �� ���� �� ����
//
//    enemies.push_back(new NormalUnit());
//    enemies.push_back(new EliteUnit());
//
//    // �� ������������ ���� ����
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
//// update �޼���: �÷��̾��� �⺻ ������ 200ms �������� �ڵ� �����ϰ� �߻�ü �� ���� ������Ʈ
//void Stage::update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window) {
//    // 200ms���� �⺻ ���� ����
//    auto now = std::chrono::steady_clock::now();
//    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAttackTime).count() > 200) {
//        player.performBasicAttack(); // �⺻ ���� ����
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
    bossSpawned = false;  // ������ �ٽ� ������ �� �ֵ��� �ʱ�ȭ
    setPlayerAttackStrategy(stageNumber, player);
    spawnEnemies(enemies);  // ���������� �´� �� ������ ����
    player.setStage(stageNumber); // Player Ŭ������ �������� ��ȣ ����

}

void Stage::spawnEnemies(std::vector<Enemy*>& enemies) {
    // ���� �� ���� ����
    for (auto* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

        // �� ������������ ���� ����
    if (stageNumber == 3 && !bossSpawned) {
        enemies.push_back(new Boss());
        bossSpawned = true;
    }

    setEnemyAttackPatterns(stageNumber, enemies);  // ���������� �´� ���� ���� ����
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

// update �޼���: �÷��̾��� �⺻ ������ 200ms �������� �ڵ� �����ϰ� �߻�ü �� ���� ������Ʈ
void Stage::update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window) {
    // 200ms���� �⺻ ���� ����
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAttackTime).count() > 200) {
        player.performBasicAttack();  // �⺻ ���� ����
        lastAttackTime = now;
    }

    // ��� ���� ���� ���� ������Ʈ �� ȭ�鿡 �׸���
    for (auto* enemy : enemies) {
        enemy->attack();     // ���� ���� ����
        enemy->draw(window); // ���� ȭ�鿡 �׸���
    }
}
