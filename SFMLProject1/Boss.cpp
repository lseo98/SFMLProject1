#include "Boss.h"
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

// ������ �ʱ� ü���� 3000, �ӵ��� 0.5�� ����
Boss::Boss() : Enemy(3000.0f, 0.5f, sf::Vector2f(0, 0), 4), attackPattern(1), beforeAttackpattern(0) {

    phase = 1;
    time = pattern1 = pattern2 = pattern3 = pattern4 = pattern5 = 0;

    // pattern 2
    pattern2LaserVisible = true;

    // pattern 4 
    maxHealUnit = 0;
    spawnHealUnitCount = 0;
    killHealUnitCount = 0;

}



void Boss::change_phase() {
    if (health < 1500.0f && attackPattern == 1) {
        attackPattern = 2;
        std::cout << "������ 2�� ��ȯ\n";
    }
    else if (health < 500.0f && attackPattern == 2) {
        attackPattern = 3;
        std::cout << "������ 3���� ��ȯ\n";
    }
    // ü�¿� ���� ������ ������ ����
}

void Boss::attack(float deltaTime) {
    time += deltaTime;

    pattern2_Laser();
    pattern4_Heal();


    /*if (time > 5) {

        attackPattern = rand() % 5 + 1;
        if (attackPattern == beforeAttackpattern) attackPattern = attackPattern % 5 + 1;
        switch (attackPattern) {
        case 1:
            std::cout << 1 << std::endl;
            break;
        case 2:
            pattern2_Laser();
            break;
        case 3:
            std::cout << 3 << std::endl;
            break;
        case 4:
            pattern4_Heal();
            break;
        case 5:
            std::cout << 5 << std::endl;
            break;
        default:
            std::cout << "Error boss attack" << std::endl;
            break;
        }
        beforeAttackpattern = attackPattern;
        time = 0;
    }*/
}
void Boss::updateAttack(float deltaTime, Player& player) {



    // patter2 ������ ���� udpate
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

    // patter4 �������� udpate
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

}

void Boss::render(sf::RenderWindow& window) {

    if (pattern2LaserVisible) {       // ������ ȿ�� �� ������ ������ �ߵ����� ��쿡�� draw
        for (sf::RectangleShape* l : lasers) {
            window.draw(*l);
        }
    }
    if (spawnHealUnitCount) {
        for (HealUnit* healUnit : healUnits) {
            healUnit->draw(window);
        }
    }
}


// pattern2 ���� �Լ�

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





// pattern4 ���� �Լ�

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
                    std::cout << "boss ä�� : " << this->getHealth() << std::endl;
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