#pragma once
#include "Enemy.h"
#include <memory>
#include "Player.h"

class Boss : public Enemy {
public:
    Boss();
    void initBoss();
    void change_phase();               // 체력에 따라 페이즈를 변경하는 메서드


    void attack(float deltaTime, Player& player, std::vector<std::unique_ptr<Missile>>& bossMissiles);
    void updateAttack(float deltaTime, Player& player, std::vector<std::unique_ptr<Missile>>& bossMissiles);

    void render(sf::RenderWindow& window, std::vector<std::unique_ptr<Missile>>& bossMissiles);

    Player* player; // 플레이어 객체에 대한 포인터
    int stageNumber;               // 현재 스테이지 번호



private:
    int phase;                                 // 보스의 페이즈 상태를 나타내는 변수
    int attackPattern;                         // 보스의 공격 패턴을 결정하는 변수
    int beforeAttackpattern;                   // 보스의 이전 공격 패턴

    // 시간 관리 변수
    float dt;
    float time;
    float pattern1;
    float pattern2;
    float pattern3;
    float pattern4;
    float pattern5;

    // 패턴 1 관련 변수
    sf::Texture missileTexture;
    int maxMissile, launchedMissile;

    // 패턴 2 관련 변수
    std::vector<sf::RectangleShape*> lasers;    // 레이저 사각형 shape
    bool pattern2LaserVisible;                  // 레이저 표출 변수

    // 패턴 3 관련 변수, 함수
    sf::RectangleShape barrier;  // 벽의 그래픽 및 위치를 나타내는 SFML RectangleShape
    bool barrierActive;          // 벽 활성화 여부를 나타내는 플래그
    bool barrierVisible;            // 벽이 현재 보이는 상태인지 여부
    sf::Clock barrierBlinkClock;    // 벽 깜빡임을 제어할 타이머
    float blinkInterval = 0.2f;     // 벽이 깜빡이는 간격 (초 단위)
    void barrierCollision(Player& player); // 플레이어의 발사체와의 충돌처리

    // 패턴 4 관련 변수, 함수
    std::vector<HealUnit*> healUnits;                           // 힐 유닛 객체
    int maxHealUnit, spawnHealUnitCount, killHealUnitCount;     // 힐 유닛 관련 카운트 변수 // 왼쪽부터 생성할 유닛수, 생성된 유닛 수, 삭제 조건에 의해 삭제된 유닛 수
    void deleteCollsionHealUnit();                              // 힐 유닛 삭제 조건 검사 및 삭제 함수

    // 패턴 5 관련 변수
    Shield shield;  // 방패 객체
    bool shieldActive;  // 방패 활성 상태

    // 패턴별 함수 5개
    void pattern1_BossMissile(sf::Vector2f playerPosition, std::vector<std::unique_ptr<Missile>>& bossMissiles); // 유도미사일
    void pattern2_Laser();
    void pattern3_Barrier(); // 벽 설치
    void pattern4_Heal();
    void pattern5_DeployShield(); // 융합로 설치



};