#pragma once
#include "Enemy.h"
#include <memory>

class Boss : public Enemy {
public:
    Boss(); 
    void change_phase();               // 체력에 따라 페이즈를 변경하는 메서드
 

    void attack(float deltaTime);
    void updateAttack(float deltaTime);

    void render(sf::RenderWindow& window);

private:
    int phase;                         // 보스의 페이즈 상태를 나타내는 변수
    
    // 시간 관리 변수
    float dt;
    float time;
    float pattern1;
    float pattern2;
    float pattern3;
    float pattern4;
    float pattern5;


    // 패턴 2 관련 변수
    std::vector<sf::RectangleShape*> laser;

    // 패턴별 함수 5개

    void pattern2_Laser();




};
