#include "Boss.h"
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

// 보스의 초기 체력은 3000, 속도는 0.5로 설정
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
        std::cout << "페이즈 2로 전환\n";
    }
    else if (health < 500.0f && attackPattern == 2) {
        attackPattern = 3;
        std::cout << "페이즈 3으로 전환\n";
    }
    // 체력에 따라 보스의 페이즈 변경
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



    // patter2 레이저 공격 udpate
    if (!lasers.empty()) {
        pattern2 += deltaTime;
        if (pattern2 < 2) {         // 공격 발동 후 2초까지
            for (sf::RectangleShape* l : lasers)
                l->setFillColor(sf::Color(255, 0, 0, 255 / 4 * pattern2));          // 레이저의 불투명도가 증가함.
        }
        else if (pattern2 < 3) {    // 공격 발동 후 2 ~ 3초
            if ((int)(pattern2 * 10) % 2 == 0) pattern2LaserVisible = false;
            else pattern2LaserVisible = true;
        }
        else {                      // 공격 발동 후 3초 후 
            for (sf::RectangleShape* laser : lasers) {
                if (laser->getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {     // 충돌 발생 시
                    player.takeDamage(1.0f);
                    player.changeHeartSprite();
                    break;
                }
            }
            pattern2LaserVisible = false;
            for (int i = 0; i < 3; i++) delete lasers[i];                            // 레이저 삭제
            lasers.clear();
        }
    }

    // patter4 힐러유닛 udpate
    if (maxHealUnit > spawnHealUnitCount) {             // 생성할 유닛 수가 될 때까지 생성
        pattern4 += deltaTime;
        if (pattern4 > 2) {                             // 2초 마다 생성
            healUnits.emplace_back(new HealUnit());
            pattern4 = 0;
            spawnHealUnitCount++;
        }
    }
    if (spawnHealUnitCount) {                           // 힐 유닛이 있을 경우에만 실행
        for (HealUnit* healUnit : healUnits) {
            healUnit->update(deltaTime);                // 위치 업데이트
        }
        player.healUnitCollision(healUnits);            // 플레이어 공격체 - 힐 유닛 충돌 처리
        deleteCollsionHealUnit();                       // 힐 유닛 삭제 조건(파괴/보스도달) 검사
    }
    if (killHealUnitCount == maxHealUnit && maxHealUnit > 0) {  // 힐 유닛 모두 삭제시 패턴 4 초기화
        for (HealUnit* healUnit : healUnits) delete healUnit;   // 힐 유닛 삭제
        healUnits.clear();
        maxHealUnit = 0;
        spawnHealUnitCount = 0;
        killHealUnitCount = 0;
    }

}

void Boss::render(sf::RenderWindow& window) {

    if (pattern2LaserVisible) {       // 깜빡임 효과 및 레이저 공격이 발동됐을 경우에만 draw
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


// pattern2 관련 함수

void Boss::pattern2_Laser() {
    int laserWidth = 100;           // laser 공격 범위
    pattern2 = 0;                   // 패턴2 시간 초기화
    pattern2LaserVisible = true;    // 깜빡임 관리 변수 초기화

    if (!lasers.empty()) {           // 기존의 레이저가 남아있다면 삭제
        for (int i = 0; i < 3; i++) delete lasers[i];
        lasers.clear();
    }
    for (int i = 0; i < 3; i++) {   // 3개의 레이저 발사
        sf::RectangleShape* laserRectangle = new sf::RectangleShape(sf::Vector2f(laserWidth, 900));
        sf::Vector2f laserPosition(0, 0);

        float x = WINDOWWIDTH / 4 + rand() % (laserWidth * 2) - 50;     // 랜덤한 x 좌표 지정
        if (x < WINDOWWIDTH / 4) x = WINDOWWIDTH / 4;                   // 만일 x 좌표가 게임 화면보다 작다면 게임 화면으로 제한
        laserPosition.x = (WINDOWWIDTH / 2) / 4 * i + x;                // 다음 레이저와 게임 화면의 약 1/4 만큼은 떨어져 있도록 조정
        laserRectangle->setPosition(laserPosition);
        laserRectangle->setFillColor(sf::Color(255, 0, 0, 1));

        lasers.push_back(laserRectangle);
    }
}





// pattern4 관련 함수

void Boss::pattern4_Heal() {

    pattern4 = 0;
    maxHealUnit = 5;                // 생성할 힐 유닛 수 5개
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

    // 화면 밖으로 나갔거나 채력이 0 이하인 적 제거
    healUnits.erase(
        std::remove_if(healUnits.begin(), healUnits.end(),
            [this](HealUnit* healUnit) {
                if (healUnit->sprite.getGlobalBounds().width + healUnit->sprite.getGlobalBounds().left > WINDOWWIDTH / 4 * 3 - 200) {   // 게임화면 우측 끝에서 왼쪽으로 200만큼 이전에 닿을 경우 보스에 도달 처리
                    this->takeDamage(-200.0f);                                          // 보스 체력 200만큼 회복
                    std::cout << "boss 채력 : " << this->getHealth() << std::endl;
                    killHealUnitCount--;
                    delete healUnit; // 메모리 해제
                    return true; // 제거 대상
                }
                else if (healUnit->getHealth() <= 0) {                                  // 플레이어 공격으로 인한 채력 0 도달 시
                    killHealUnitCount--;
                    delete healUnit; // 메모리 해제
                    return true; // 제거 대상
                }
                return false; // 유지 대상
            }),
        healUnits.end());

}