#pragma once
#include "Enemy.h"
#include <memory>
#include "Player.h"

class Boss : public Enemy {
public:
    Boss();
    void change_phase();               // 체력에 따라 페이즈를 변경하는 메서드


    void attack(float deltaTime);
    void updateAttack(float deltaTime, Player& player);

    void render(sf::RenderWindow& window);

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


    // 패턴 2 관련 변수
    std::vector<sf::RectangleShape*> lasers;    // 레이저 사각형 shape
    bool pattern2LaserVisible;                  // 레이저 표출 변수


    // 패턴 4 관련 변수

    std::vector<HealUnit*> healUnits;                           // 힐 유닛 객체
    int maxHealUnit, spawnHealUnitCount, killHealUnitCount;     // 힐 유닛 관련 카운트 변수 // 왼쪽부터 생성할 유닛수, 생성된 유닛 수, 삭제 조건에 의해 삭제된 유닛 수
    void deleteCollsionHealUnit();                              // 힐 유닛 삭제 조건 검사 및 삭제 함수

    // 패턴별 함수 5개

    void pattern2_Laser();

    void pattern4_Heal();




};