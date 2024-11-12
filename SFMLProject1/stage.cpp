#include "Stage.h"
#include "SkyPlayerAttack.h"
#include "SeaPlayerAttack.h"
#include "LandPlayerAttack.h"
#include "SkyEnemyAttack.h"
#include "SeaEnemyAttack.h"
#include "LandEnemyAttack.h"
#include <memory>
#include <chrono>

Stage::Stage() : stageNumber(1), bossSpawned(false), lastAttackTime(std::chrono::steady_clock::now()) { }

void Stage::setStage(int stageNumber, Player& player, std::vector<Enemy*>& enemies) {
    this->stageNumber = stageNumber;

    setPlayerAttack(stageNumber, player);
    setEnemyAttack(stageNumber, enemies);
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
        player.setPlayerAttack(std::make_unique<SkyPlayerAttack>());
    }
    else if (stageNumber == 2) {
        player.setPlayerAttack(std::make_unique<SeaPlayerAttack>());
    }
    else if (stageNumber == 3) {
        player.setPlayerAttack(std::make_unique<LandPlayerAttack>());
    }
}

void Stage::setEnemyAttack(int stageNumber, std::vector<Enemy*>& enemies) {
    for (auto* enemy : enemies) {
        AttackType type = dynamic_cast<NormalUnit*>(enemy) ? AttackType::Normal : AttackType::Elite;
        std::unique_ptr<EnemyAttack> attackPattern;
        if (stageNumber == 1) {
            attackPattern = std::make_unique<SkyEnemyAttack>(type);
        }
        else if (stageNumber == 2) {
            attackPattern = std::make_unique<SeaEnemyAttack>(type);
        }
        else if (stageNumber == 3) {
            attackPattern = std::make_unique<LandEnemyAttack>(type);
        }
        enemy->setEnemyAttack(std::move(attackPattern));
    }
}

// update 메서드: 플레이어의 기본 공격을 200ms 간격으로 자동 실행하고 발사체 및 적을 업데이트
void Stage::update(Player& player, std::vector<Enemy*>& enemies, sf::RenderWindow& window) {
    // 200ms마다 기본 공격 수행
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastAttackTime).count() > 200) {
        player.performBasicAttack(); // 기본 공격 수행
        lastAttackTime = now;
    }


}