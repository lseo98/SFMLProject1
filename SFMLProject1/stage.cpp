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

    // �������� ���� �� �� �ʱ�ȭ
    for (auto* enemy : enemies) {
        delete enemy; // ���� �� ����
    }
    enemies.clear(); // ���� �ʱ�ȭ

    // ��� �� ����
    sf::FloatRect viewRect(450, 0, 900, 900); // ũ��: 900x900
    backgroundView.reset(viewRect);

    // Viewport ����
    backgroundView.setViewport(sf::FloatRect(
        450.f / 1800.f, // ��� x ��ġ
        0.f,            // ��� y ��ġ
        900.f / 1800.f, // ��� �ʺ�
        1.f             // ��� ����
    ));

    // ��� ����
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
        scrollSpeed = 0.0f;  // �� ���������� ������ ���
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite1.setTexture(backgroundTexture);

    backgroundSprite.setPosition(450, 0);  // ȭ�� �߾� ������ ��� ����  
    backgroundSprite1.setPosition(450, -(float)backgroundTexture.getSize().y);

    setPlayerAttack(stageNumber, player);
    setEnemyAttack(stageNumber, enemies);
}

void Stage::drawBackground(sf::RenderWindow& window) {
    // ���� �� ����
    sf::View originalView = window.getView();

    // ��� �� ����
    window.setView(backgroundView);
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
        if (backgroundXPos <= -450) {
            backgroundXPos = 450;  // ��ũ�� ��ġ �ʱ�ȭ
        }
        backgroundSprite.setPosition(backgroundXPos, 0);
        backgroundSprite1.setPosition(backgroundXPos + 900, 0);
    }

    // â�� ������ ����(450~1350) ������ ��� ���
    window.draw(backgroundSprite);
    window.draw(backgroundSprite1);
    window.setView(originalView);

}

void Stage::spawnEnemies(std::vector<Enemy*>& enemies, float deltaTime) {
    // �ð� ����
    timeSinceLastAttack += deltaTime;

    // �� ���� �ֱ�
    if (timeSinceLastAttack >= spawnInterval && enemies.size() < maxEnemies) {
        float normalUnitStartX = 0, normalUnitStartY = 0;
        float eliteUnitStartX = 0, eliteUnitStartY = 0;

        if (stageNumber == 1) { // �ϴ� ��������: �� ������ ���� X ��ġ
            normalUnitStartX = rand() % (1350 - 450) + 450; // �Ϲ� ���� X ��ǥ: ȭ���� �߾� ����
            normalUnitStartY = -50;                           // �Ϲ� ���� Y ��ǥ: ȭ�� ���

            eliteUnitStartX = rand() % (1350 - 450) + 450;  // ���� ���� X ��ǥ: ȭ���� �߾� ����
            eliteUnitStartY = -50;                            // ���� ���� Y ��ǥ: ȭ�� ���
        }
        else if (stageNumber == 2) { // �ٴ� ��������: �� �����ʿ��� ���� Y ��ġ
            normalUnitStartX = 1400;                        // �Ϲ� ���� X ��ǥ: ȭ�� ������ ��
            normalUnitStartY = rand() % 900;                // �Ϲ� ���� Y ��ǥ: ȭ�� ��ü ����

            eliteUnitStartX = 1400;                         // ���� ���� X ��ǥ: ȭ�� ������ ��
            eliteUnitStartY = rand() % 900;                 // ���� ���� Y ��ǥ: ȭ�� ��ü ����
        }
        else if (stageNumber == 3) { // �� ��������: �� �� �� �Ʒ�
            if (rand() % 2 == 0) {
                normalUnitStartX = 400; // �Ϲ� ���� ���� ����
            }
            else {
                normalUnitStartX = 1400; // �Ϲ� ���� ������ ����
            }
            normalUnitStartY = 700; // �Ϲ� ���� Y ��ǥ: ȭ�� �Ʒ�

            if (rand() % 2 == 0) {
                eliteUnitStartX = 400; // ���� ���� ���� ����
            }
            else {
                eliteUnitStartX = 1400; // ���� ���� ������ ����
            }
            eliteUnitStartY = 200; // ���� ���� Y ��ǥ: ȭ�� ��
        }

        // �Ϲ� ���� ����
        NormalUnit* normalUnit = new NormalUnit(stageNumber, sf::Vector2f(normalUnitStartX, normalUnitStartY));
        if (stageNumber == 3) {
            int direction = (normalUnitStartX == 400) ? 1 : -1; // ���ʿ��� �����ϸ� ����������, �����ʿ��� �����ϸ� ��������
            normalUnit->updateDirection(direction);
        }
        enemies.push_back(normalUnit);

        // ���� ���� ����
        EliteUnit* eliteUnit = new EliteUnit(stageNumber, sf::Vector2f(eliteUnitStartX, eliteUnitStartY));
        if (stageNumber == 3) {
            int direction = (eliteUnitStartX == 400) ? 1 : -1; // ���ʿ��� �����ϸ� ����������, �����ʿ��� �����ϸ� ��������
            eliteUnit->updateDirection(direction);
        }
        //eliteUnit->initializeRandomSpeeds(); // ���� ������ ���� �ӵ� �ʱ�ȭ
        enemies.push_back(eliteUnit);

        // Ÿ�̸� �ʱ�ȭ
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
            //    enemy->image("sky_enemy_unit.png");   // �̹��� ����
            //}
            //else {
            //    enemy->image("sky_elite_unit.png");
            //}
        }
        else if (stageNumber == 2) {
            attackPattern = std::make_unique<SeaEnemyAttack>(type);
            //if (type == AttackType::Normal) {
            //    enemy->image("sea_enemy_unit.png");   // �̹��� ����
            //}
            //else {
            //    enemy->image("sea_elite_unit.png");
            //}
        }
        else if (stageNumber == 3) {
            attackPattern = std::make_unique<LandEnemyAttack>(type);
            //if (type == AttackType::Normal) {
            //    enemy->image("land_enemy_unit.png");   // �̹��� ����
            //}
            //else {
            //    enemy->image("land_elite_unit.png");
            //}
        }
        enemy->setEnemyAttack(std::move(attackPattern));
    }
}

//// update �޼���: �÷��̾��� �⺻ ������ 200ms �������� �ڵ� ����
//void Stage::update(Player& player, float deltaTime) {
//    // ��Ÿ Ÿ���� �����Ͽ� 200ms���� �⺻ ���� ����
//    timeSinceLastAttack += deltaTime;
//
//    if (timeSinceLastAttack >= 0.2f) { // 200ms �������� ����
//        player.performBasicAttack();   // �⺻ ���� ����
//        timeSinceLastAttack = 0.0f;    // ���� ���� �ʱ�ȭ
//    }
//}