#include "Boss.h"
#include "Game.h"
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

// 보스의 초기 체력은 3000, 속도는 0.5로 설정
Boss::Boss() : Enemy(3000.0f, 0.5f, sf::Vector2f(1300, 200), 4) {
    initBoss();
}
void Boss::initBoss() {
    health = 3000;
    phase = 1;
    time = pattern1 = pattern2 = pattern3 = pattern4 = pattern5 = 0;
    attackPattern = 1;
    beforeAttackpattern = 0;

    // 보스 이미지 삽입 
    sf::IntRect textureRect;  // 표시할 텍스처 영역
    textureRect = sf::IntRect(5, 75, 650, 650);
    image("sky_elite_unit.png", textureRect);  // 이미지 파일을 초기화
  
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

    // 벽 크기, 위치, 색상 동적 설정
    barrier.setSize(sf::Vector2f(20.0f, 500.0f));  // 가로 20, 세로 500 크기
    barrier.setFillColor(sf::Color(70, 70, 70));     // 어두운 회색
    barrier.setPosition(1100.0f, 275.0f);            // 새로운 위치 설정
}

void Boss::change_phase() {
    if (health < 1500.0f && attackPattern == 1) {
        attackPattern = 2;
        //std::cout << "페이즈 2로 전환\n";
    }
    else if (health < 500.0f && attackPattern == 2) {
        attackPattern = 3;
       // std::cout << "페이즈 3으로 전환\n";
    }
    // 체력에 따라 보스의 페이즈 변경
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
        if (attackPattern == beforeAttackpattern) attackPattern = attackPattern % 5 + 1;    // 1 ~ 5 사이의 패턴 생성
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
    // pattern1 보스미사일 update
    pattern1 += deltaTime;

    // 2초마다 보스미사일 발사
    if (pattern1 >= 2.0f && maxMissile - 1 > launchedMissile) {
        pattern1_BossMissile(player.getPosition(), bossMissiles);
        pattern1 = 0.0f; // 시간 초기화
        launchedMissile++;
        if (maxMissile - 1 == launchedMissile) { maxMissile = 0; launchedMissile = 0; }
    }

    // 모든 보스 미사일 업데이트
    for (auto& missile : bossMissiles) {
        missile->isPlayerProjectile = false;
        missile->update();
    }

    // pattern2 레이저 공격 update
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

    // pattern3 벽 설치 update
    if (barrierActive) {
        // 벽 활성화 상태일 때 항상 보이도록 설정
        if (pattern3 == 0.0f) { // 패턴 시작 시 초기화
            barrierVisible = true;
        }
        pattern3 += deltaTime; // 벽 활성 상태에서 시간 증가

        barrierCollision(player);
        
        if (pattern3 >= 8.0f) { // 벽이 사라지기 2초 전부터 깜빡임
            if (barrierBlinkClock.getElapsedTime().asSeconds() >= blinkInterval) {
                barrierVisible = !barrierVisible; // 보이는 상태를 토글
                barrierBlinkClock.restart();     // 타이머 초기화
            }
        }

        if (pattern3 >= 10.0f) { // 벽이 10초 동안 유지되면 제거
            barrierActive = false;
            barrierVisible = false; // 깜빡임 상태 초기화
        }
    }


    // pattern4 힐러유닛 udpate
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

    // pattern5 융합로 설치 update
    if (shieldActive) {
        pattern5 += deltaTime;
        std::vector<Shield*> tempEnemies;
        tempEnemies.push_back(&shield);
        player.shieldCollision(tempEnemies);

        if (pattern5 > 5) {
            shieldActive = false; // 5초 후 융합로 터져서 없어질 때 폭발 효과 넣어야 함
            player.takeDamage(1.0f);
            player.changeHeartSprite();
        }

        if (shield.getHealth() <= 0.0f) {
            shieldActive = false; // 방패 비활성화
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
    if (pattern2LaserVisible) {       // 깜빡임 효과 및 레이저 공격이 발동됐을 경우에만 draw
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
        shield.draw(window); // 방패 그리기
    }
}

// 보스 패턴(1 ~ 5) 함수
// 패턴 1 관련 함수
void Boss::pattern1_BossMissile(sf::Vector2f playerPosition, std::vector<std::unique_ptr<Missile>>& bossMissiles) {
    maxMissile = 5;
    // 목표 방향 계산
    sf::Vector2f updatedDirection = playerPosition - position;
    float magnitude = std::sqrt(updatedDirection.x * updatedDirection.x + updatedDirection.y * updatedDirection.y);
    if (magnitude != 0) {
        updatedDirection /= magnitude; // 방향 벡터를 정규화
    }

    // 새로운 미사일 생성
    auto newMissile = std::make_unique<Missile>(position, updatedDirection, 5.0f); // 보스 위치에서 생성

    // 텍스처 설정
    if (!missileTexture.loadFromFile("missile_land.png")) {
        std::cerr << "Failed to load missile_land.png!" << std::endl;
    }

    newMissile->setTexture(missileTexture, sf::IntRect());

    bossMissiles.push_back(std::move(newMissile));
}

// 패턴 2 관련 함수
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

// 패턴 3 관련 함수
void Boss::pattern3_Barrier() {
    if (!barrierActive) {
        barrierActive = true;    // 벽 활성화
        pattern3 = 0.0f;    // 벽 지속 시간 초기화   
    }
}

void Boss::barrierCollision(Player& player) {
    if (!barrierActive) return; // 벽이 활성화되지 않았다면 처리하지 않음

    // 일반 공격 충돌 처리
    auto& normalAttacks = player.getBullets(); // 플레이어 일반 공격 벡터 가져오기
    for (size_t i = 0; i < normalAttacks.size(); ++i) {
        if (normalAttacks[i]->sprite.getGlobalBounds().intersects(barrier.getGlobalBounds())) {
            // 충돌한 일반 공격 제거
            delete normalAttacks[i];
            normalAttacks.erase(normalAttacks.begin() + i);
            --i; // 인덱스 조정
        }
    }

    // 미사일 공격 충돌 처리
    auto& missiles = player.getMissiles(); // 플레이어 미사일 벡터 가져오기
    for (size_t i = 0; i < missiles.size(); ++i) {
        if (missiles[i]->sprite.getGlobalBounds().intersects(barrier.getGlobalBounds())) {
            // 충돌한 미사일 제거
            delete missiles[i];
            missiles.erase(missiles.begin() + i);
            --i; // 인덱스 조정
        }
    }

    // 궁극기 공격 충돌 처리
    auto& ultimates = player.getAllyMissiles(); // 플레이어 궁극기 공격 벡터 가져오기
    for (size_t i = 0; i < ultimates.size(); ++i) {
        if (ultimates[i]->sprite.getGlobalBounds().intersects(barrier.getGlobalBounds())) {
            // 충돌한 궁극기 제거
            delete ultimates[i];
            ultimates.erase(ultimates.begin() + i);
            --i; // 인덱스 조정
        }
    }
}


// 패턴 4 관련 함수
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
                    //std::cout << "boss 체력 : " << this->getHealth() << std::endl;
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

// 패턴 5 관련 함수
void Boss::pattern5_DeployShield() {
    if (!shieldActive) {
        shieldActive = true; // 방패 활성화 

        shield = Shield(); // 새 Shield 객체 생성
        shield.image("land_elite_unit_left.png"); // 이미지를 다시 설정

    }
}