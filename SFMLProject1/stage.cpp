#include "Stage.h"
#include <memory>

Stage::Stage() : stageNumber(1), bossSpawned(false), timeSinceLastAttack(0.0f), attackCooldown(0.2f) { }

void Stage::setStage(int stageNumber, std::vector<Enemy*>& enemies) {
    this->stageNumber = stageNumber;
    // ��� ����
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
        scrollSpeed = 0.0f;  // �� ���������� ������ ���
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite1.setTexture(backgroundTexture);

    backgroundSprite.setPosition(450, 0);  // ȭ�� �߾� ������ ��� ����
    backgroundSprite1.setPosition(450, -(float)backgroundTexture.getSize().y);


    //setEnemyAttack(stageNumber, enemies);   // �����ؾ�
}

void Stage::drawBackground(sf::RenderWindow& window) {
    if (stageNumber == 1) { // �ϴ� ��������: ���� ��ũ��
        backgroundYPos += scrollSpeed;
        if (backgroundYPos >= backgroundTexture.getSize().y) {
            backgroundYPos = 0;  // ��ũ�� ��ġ �ʱ�ȭ
        }
        backgroundSprite.setPosition(450, backgroundYPos);
        backgroundSprite1.setPosition(450, backgroundYPos - backgroundTexture.getSize().y);
    }
    else if (stageNumber == 2) { // �ٴ� ��������: ������ ��ũ��
        backgroundXPos -= scrollSpeed;
        if (backgroundXPos >= backgroundTexture.getSize().x) {
            backgroundXPos = 450;  // ��ũ�� ��ġ �ʱ�ȭ
        }
        backgroundSprite.setPosition(450 + backgroundXPos, 0);
        backgroundSprite1.setPosition(450 + backgroundXPos + backgroundTexture.getSize().x, 0);
    }

    // â�� ������ ����(450~1350) ������ ��� ���
    window.draw(backgroundSprite);
    window.draw(backgroundSprite1);
}

void Stage::spawnEnemies(std::vector<Enemy*>& enemies) {
    enemies.clear(); // �������� ���� �� ���� �� ����

    enemies.push_back(new NormalUnit(stageNumber));
    enemies.push_back(new EliteUnit(stageNumber));

    // �� ������������ ���� ����
    if (stageNumber == 3 && !bossSpawned) {
        enemies.push_back(new Boss());
        bossSpawned = true;
    }
}



void Stage::setEnemyAttack(int stageNumber, std::vector<Enemy*>& enemies) {
    for (auto* enemy : enemies) {


        //if (stageNumber == 1) {

        //    if (type == AttackType::Normal) {
        //        enemy->image("sky_enemy_unit.png");   // �̹��� ����
        //    }
        //    else {
        //        enemy->image("sky_elite_unit.png");
        //    }
        //}
        //else if (stageNumber == 2) {
        //    attackPattern = std::make_unique<SeaEnemyAttack>(type);
        //    if (type == AttackType::Normal) {
        //        enemy->image("sea_enemy_unit.png");   // �̹��� ����
        //    }
        //    else {
        //        enemy->image("sea_elite_unit.png");
        //    }
        //}
        //else if (stageNumber == 3) {
        //    attackPattern = std::make_unique<LandEnemyAttack>(type);
        //    if (type == AttackType::Normal) {
        //        enemy->image("land_enemy_unit.png");   // �̹��� ����
        //    }
        //    else {
        //        enemy->image("land_elite_unit.png");
        //    }
        //}

    }
}

