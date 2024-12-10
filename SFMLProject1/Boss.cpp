#include "Boss.h"
#include "Game.h"
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

// ������ �ʱ� ü���� 3000, �ӵ��� 0.5�� ����
Boss::Boss() : Enemy(3000.0f, 0.5f, sf::Vector2f(1300, 200), 4) {
    initBoss();
}
void Boss::initBoss() {
    health = 3000;
    phase = 1;
    time = pattern1 = pattern2 = pattern3 = pattern4 = pattern5 = 0;
    attackPattern = 1;
    beforeAttackpattern = 0;

    // ���� �̹��� ���� 
    sf::IntRect textureRect;  // ǥ���� �ؽ�ó ����
    textureRect = sf::IntRect(5, 75, 650, 650);
    image("sky_elite_unit.png", textureRect);  // �̹��� ������ �ʱ�ȭ
  
    setPosition(sf::Vector2f(WINDOWWIDTH*3/4-100, WINDOWHEIGHT - 200));


    // pattern 1
    maxMissile = 0;
    launchedMissile = 0;

    // pattern 2
    pattern2LaserVisible = true;
    for (sf::RectangleShape* l : lasers) {
        delete l;
    }
    lasers.clear();

    // pattern 3
    barrierActive = false;
    barrierVisible = false;

    // pattern 4 
    maxHealUnit = 0;
    spawnHealUnitCount = 0;
    killHealUnitCount = 0;
    for (HealUnit* healUnit : healUnits) {
        delete healUnit;
    }
    healUnits.clear();

    // pattern 5
    shieldActive = false;

    // �� ũ��, ��ġ, ���� ���� ����
    barrier.setSize(sf::Vector2f(20.0f, 500.0f));  // ���� 20, ���� 500 ũ��
    barrier.setFillColor(sf::Color(70, 70, 70));     // ��ο� ȸ��
    barrier.setPosition(1100.0f, 275.0f);            // ���ο� ��ġ ����
}

void Boss::change_phase() {
    if (health < 1500.0f && attackPattern == 1) {
        attackPattern = 2;
        //std::cout << "������ 2�� ��ȯ\n";
    }
    else if (health < 500.0f && attackPattern == 2) {
        attackPattern = 3;
       // std::cout << "������ 3���� ��ȯ\n";
    }
    // ü�¿� ���� ������ ������ ����
}

void Boss::attack(float deltaTime, Player& player, std::vector<std::unique_ptr<Missile>>& bossMissiles) {
    time += deltaTime;

    /*pattern1_BossMissile(player.getPosition(), bossMissiles);
    pattern2_Laser();
    pattern3_Barrier();
    pattern4_Heal();
    pattern5_DeployShield();*/


    if (time > 10) {

        attackPattern = rand() % 5 + 1;
        if (attackPattern == beforeAttackpattern) attackPattern = attackPattern % 5 + 1;    // 1 ~ 5 ������ ���� ����
        //std::cout << getHealth() << std::endl;
        switch (attackPattern) {
        case 1:
            pattern1_BossMissile(player.getPosition(), bossMissiles);
            break;
        case 2:
            pattern2_Laser();
            break;
        case 3:
            pattern3_Barrier();
            break;
        case 4:
            pattern4_Heal();
            break;
        case 5:
            pattern5_DeployShield();
            break;
        default:
           // std::cout << "Error boss attack" << std::endl;
            break;
        }
        beforeAttackpattern = attackPattern;
        time = 0;
    }
}
void Boss::updateAttack(float deltaTime, Player& player, std::vector<std::unique_ptr<Missile>>& bossMissiles) {
    // pattern1 �����̻��� update
    pattern1 += deltaTime;

    // 2�ʸ��� �����̻��� �߻�
    if (pattern1 >= 2.0f && maxMissile - 1 > launchedMissile) {
        pattern1_BossMissile(player.getPosition(), bossMissiles);
        pattern1 = 0.0f; // �ð� �ʱ�ȭ
        launchedMissile++;
        if (maxMissile - 1 == launchedMissile) { maxMissile = 0; launchedMissile = 0; }
    }

    // ��� ���� �̻��� ������Ʈ
    for (auto& missile : bossMissiles) {
        missile->isPlayerProjectile = false;
        missile->update();
    }

    // pattern2 ������ ���� update
    if (!lasers.empty()) {
        pattern2 += deltaTime;
        if (pattern2 < 2) {         // ���� �ߵ� �� 2�ʱ���
            for (sf::RectangleShape* l : lasers)
                l->setFillColor(sf::Color(255, 0, 0, 255 / 4 * pattern2));          // �������� �������� ������.
        }
        else if (pattern2 < 3) {    // ���� �ߵ� �� 2 ~ 3��
            if ((int)(pattern2 * 10) % 2 == 0) pattern2LaserVisible = false;
            else pattern2LaserVisible = true;
        }
        else {                      // ���� �ߵ� �� 3�� �� 
            for (sf::RectangleShape* laser : lasers) {
                if (laser->getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {     // �浹 �߻� ��
                    player.takeDamage(1.0f);
                    player.changeHeartSprite();
                    break;
                }
            }
            pattern2LaserVisible = false;
            for (int i = 0; i < 3; i++) delete lasers[i];                            // ������ ����
            lasers.clear();
        }
    }

    // pattern3 �� ��ġ update
    if (barrierActive) {
        // �� Ȱ��ȭ ������ �� �׻� ���̵��� ����
        if (pattern3 == 0.0f) { // ���� ���� �� �ʱ�ȭ
            barrierVisible = true;
        }
        pattern3 += deltaTime; // �� Ȱ�� ���¿��� �ð� ����

        barrierCollision(player);
        
        if (pattern3 >= 8.0f) { // ���� ������� 2�� ������ ������
            if (barrierBlinkClock.getElapsedTime().asSeconds() >= blinkInterval) {
                barrierVisible = !barrierVisible; // ���̴� ���¸� ���
                barrierBlinkClock.restart();     // Ÿ�̸� �ʱ�ȭ
            }
        }

        if (pattern3 >= 10.0f) { // ���� 10�� ���� �����Ǹ� ����
            barrierActive = false;
            barrierVisible = false; // ������ ���� �ʱ�ȭ
        }
    }


    // pattern4 �������� udpate
    if (maxHealUnit > spawnHealUnitCount) {             // ������ ���� ���� �� ������ ����
        pattern4 += deltaTime;
        if (pattern4 > 2) {                             // 2�� ���� ����
            healUnits.emplace_back(new HealUnit());
            pattern4 = 0;
            spawnHealUnitCount++;
        }
    }
    if (spawnHealUnitCount) {                           // �� ������ ���� ��쿡�� ����
        for (HealUnit* healUnit : healUnits) {
            healUnit->update(deltaTime);                // ��ġ ������Ʈ
        }
        player.healUnitCollision(healUnits);            // �÷��̾� ����ü - �� ���� �浹 ó��
        deleteCollsionHealUnit();                       // �� ���� ���� ����(�ı�/��������) �˻�
    }
    if (killHealUnitCount == maxHealUnit && maxHealUnit > 0) {  // �� ���� ��� ������ ���� 4 �ʱ�ȭ
        for (HealUnit* healUnit : healUnits) delete healUnit;   // �� ���� ����
        healUnits.clear();
        maxHealUnit = 0;
        spawnHealUnitCount = 0;
        killHealUnitCount = 0;
    }

    // pattern5 ���շ� ��ġ update
    if (shieldActive) {
        pattern5 += deltaTime;
        std::vector<Shield*> tempEnemies;
        tempEnemies.push_back(&shield);
        player.shieldCollision(tempEnemies);

        if (pattern5 > 5) {
            shieldActive = false; // 5�� �� ���շ� ������ ������ �� ���� ȿ�� �־�� ��
            player.takeDamage(1.0f);
            player.changeHeartSprite();
        }

        if (shield.getHealth() <= 0.0f) {
            shieldActive = false; // ���� ��Ȱ��ȭ
        }
    }

}

void Boss::render(sf::RenderWindow& window, std::vector<std::unique_ptr<Missile>>& bossMissiles) {
    
    this->draw(window);
    
    // pattern1
    for (const auto& missile : bossMissiles) {
        missile->draw(window);
    }

    // pattern2
    if (pattern2LaserVisible) {       // ������ ȿ�� �� ������ ������ �ߵ����� ��쿡�� draw
        for (sf::RectangleShape* l : lasers) {
            window.draw(*l);
        }
    }

    // pattern3
    if (barrierActive && barrierVisible) {
        window.draw(barrier);
    }


    // pattern4
    if (spawnHealUnitCount) {
        for (HealUnit* healUnit : healUnits) {
            healUnit->draw(window);
        }
    }

    // pattern5
    if (shieldActive) {
        shield.draw(window); // ���� �׸���
    }
}

// ���� ����(1 ~ 5) �Լ�
// ���� 1 ���� �Լ�
void Boss::pattern1_BossMissile(sf::Vector2f playerPosition, std::vector<std::unique_ptr<Missile>>& bossMissiles) {
    maxMissile = 5;
    // ��ǥ ���� ���
    sf::Vector2f updatedDirection = playerPosition - position;
    float magnitude = std::sqrt(updatedDirection.x * updatedDirection.x + updatedDirection.y * updatedDirection.y);
    if (magnitude != 0) {
        updatedDirection /= magnitude; // ���� ���͸� ����ȭ
    }

    // ���ο� �̻��� ����
    auto newMissile = std::make_unique<Missile>(position, updatedDirection, 5.0f); // ���� ��ġ���� ����

    // �ؽ�ó ����
    if (!missileTexture.loadFromFile("missile_land.png")) {
        std::cerr << "Failed to load missile_land.png!" << std::endl;
    }

    newMissile->setTexture(missileTexture, sf::IntRect());

    bossMissiles.push_back(std::move(newMissile));
}

// ���� 2 ���� �Լ�
void Boss::pattern2_Laser() {
    int laserWidth = 100;           // laser ���� ����
    pattern2 = 0;                   // ����2 �ð� �ʱ�ȭ
    pattern2LaserVisible = true;    // ������ ���� ���� �ʱ�ȭ

    if (!lasers.empty()) {           // ������ �������� �����ִٸ� ����
        for (int i = 0; i < 3; i++) delete lasers[i];
        lasers.clear();
    }
    for (int i = 0; i < 3; i++) {   // 3���� ������ �߻�
        sf::RectangleShape* laserRectangle = new sf::RectangleShape(sf::Vector2f(laserWidth, 900));
        sf::Vector2f laserPosition(0, 0);

        float x = WINDOWWIDTH / 4 + rand() % (laserWidth * 2) - 50;     // ������ x ��ǥ ����
        if (x < WINDOWWIDTH / 4) x = WINDOWWIDTH / 4;                   // ���� x ��ǥ�� ���� ȭ�麸�� �۴ٸ� ���� ȭ������ ����
        laserPosition.x = (WINDOWWIDTH / 2) / 4 * i + x;                // ���� �������� ���� ȭ���� �� 1/4 ��ŭ�� ������ �ֵ��� ����
        laserRectangle->setPosition(laserPosition);
        laserRectangle->setFillColor(sf::Color(255, 0, 0, 1));

        lasers.push_back(laserRectangle);
    }
}

// ���� 3 ���� �Լ�
void Boss::pattern3_Barrier() {
    if (!barrierActive) {
        barrierActive = true;    // �� Ȱ��ȭ
        pattern3 = 0.0f;    // �� ���� �ð� �ʱ�ȭ   
    }
}

void Boss::barrierCollision(Player& player) {
    if (!barrierActive) return; // ���� Ȱ��ȭ���� �ʾҴٸ� ó������ ����

    // �Ϲ� ���� �浹 ó��
    auto& normalAttacks = player.getBullets(); // �÷��̾� �Ϲ� ���� ���� ��������
    for (size_t i = 0; i < normalAttacks.size(); ++i) {
        if (normalAttacks[i]->sprite.getGlobalBounds().intersects(barrier.getGlobalBounds())) {
            // �浹�� �Ϲ� ���� ����
            delete normalAttacks[i];
            normalAttacks.erase(normalAttacks.begin() + i);
            --i; // �ε��� ����
        }
    }

    // �̻��� ���� �浹 ó��
    auto& missiles = player.getMissiles(); // �÷��̾� �̻��� ���� ��������
    for (size_t i = 0; i < missiles.size(); ++i) {
        if (missiles[i]->sprite.getGlobalBounds().intersects(barrier.getGlobalBounds())) {
            // �浹�� �̻��� ����
            delete missiles[i];
            missiles.erase(missiles.begin() + i);
            --i; // �ε��� ����
        }
    }

    // �ñر� ���� �浹 ó��
    auto& ultimates = player.getAllyMissiles(); // �÷��̾� �ñر� ���� ���� ��������
    for (size_t i = 0; i < ultimates.size(); ++i) {
        if (ultimates[i]->sprite.getGlobalBounds().intersects(barrier.getGlobalBounds())) {
            // �浹�� �ñر� ����
            delete ultimates[i];
            ultimates.erase(ultimates.begin() + i);
            --i; // �ε��� ����
        }
    }
}


// ���� 4 ���� �Լ�
void Boss::pattern4_Heal() {
    pattern4 = 0;
    maxHealUnit = 5;                // ������ �� ���� �� 5��
    spawnHealUnitCount = 0;
    killHealUnitCount = 0;
    if (!healUnits.empty()) {
        for (int i = 0; i < healUnits.size(); i++) delete healUnits[i];
        healUnits.clear();
    }

    healUnits.push_back(new HealUnit());
    spawnHealUnitCount++;
}

void Boss::deleteCollsionHealUnit() {

    // ȭ�� ������ �����ų� ä���� 0 ������ �� ����
    healUnits.erase(
        std::remove_if(healUnits.begin(), healUnits.end(),
            [this](HealUnit* healUnit) {
                if (healUnit->sprite.getGlobalBounds().width + healUnit->sprite.getGlobalBounds().left > WINDOWWIDTH / 4 * 3 - 200) {   // ����ȭ�� ���� ������ �������� 200��ŭ ������ ���� ��� ������ ���� ó��
                    this->takeDamage(-200.0f);                                          // ���� ü�� 200��ŭ ȸ��
                    //std::cout << "boss ü�� : " << this->getHealth() << std::endl;
                    killHealUnitCount--;
                    delete healUnit; // �޸� ����
                    return true; // ���� ���
                }
                else if (healUnit->getHealth() <= 0) {                                  // �÷��̾� �������� ���� ä�� 0 ���� ��
                    killHealUnitCount--;
                    delete healUnit; // �޸� ����
                    return true; // ���� ���
                }
                return false; // ���� ���
            }),
        healUnits.end());

}

// ���� 5 ���� �Լ�
void Boss::pattern5_DeployShield() {
    if (!shieldActive) {
        shieldActive = true; // ���� Ȱ��ȭ 

        shield = Shield(); // �� Shield ��ü ����
        shield.image("land_elite_unit_left.png"); // �̹����� �ٽ� ����

    }
}