#pragma once
#include "Character.h"
#include "Missile.h"
#include <iostream>
class Player;

extern int WINDOWWIDTH, WINDOWHEIGHT;

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position, int stageNumber);

   
    void draw(sf::RenderWindow& window);

    void update(float deltaTime);
    void collision(Player &player);

    void image(const std::string& textureFile);

    void updateDirection(int newDirection = 0); // 방향 가져오기 

    bool isOffScreen() const; // 중앙 900x900 범위를 기준으로 화면 밖으로 나갔는지 확인

    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트

protected:
    int stageNumber;  // 스테이지 번호
    int direction;    // 땅 스테이지에서만 사용되는 방향 (1: 오른쪽, -1: 왼쪽)

    float targetX = 0.0f; // 목표 X 좌표
    float targetY = 0.0f; // 목표 Y 좌표
    float nextTargetY = 0.0f; // 하늘 스테이지: 다음 Y 목표값
    float nextTargetX = 1350.0f; // 바다 스테이지: 다음 X 목표값

    bool collisionFlag;

};

class NormalUnit : public Enemy {

public:
    NormalUnit(int stageNumber, sf::Vector2f position,int direction)
        : Enemy(100.0f, 1.0f, position, stageNumber) {
        this->direction = direction; // 방향 설정

        if (stageNumber == 3) { // 땅 스테이지
            if(direction==-1)
                image("land_enemy_unit.png"); 
            if(direction==1)
                image("land_enemy_unit_right.png");
        }
        else {
            image(stageNumber == 1 ? "sky_enemy_unit.png" :
                stageNumber == 2 ? "sea_enemy_unit_b.png" :
                "land_enemy_unit.png");
        }
    }

    /*void collision() {

    }*/



};

class EliteUnit : public Enemy {

public:
    EliteUnit(int stageNumber, sf::Vector2f position,int direction)
        : Enemy(300.0f, 1.5f, position, stageNumber) {
        
        missileLaunched = false;
        this->direction = direction; // 방향 설정
        //if (stageNumber == 3) { // 땅 스테이지
        //    if (direction == -1)
        //        image("land_elite_unit_left.png");
        //    else if (direction == 1)
        //        image("land_elite_unit_right.png");
        //}
        //else {
        //    image(stageNumber == 1 ? "sky_elite_unit.png" :
        //        stageNumber == 2 ? "sea_elite_unit.png" :
        //        "land_elite_unit.png");
        //}
        // 위에 다 스위치로 처리
       switch (stageNumber) {
       case 1:
           image("sky_elite_unit.png");  // 이미지 파일을 초기화
           missileDirection = sf::Vector2f(0, 1);
           break;
       case 2:
           image("sea_elite_unit.png");  // 이미지 파일을 초기화
           missileDirection = sf::Vector2f(-1, 0);
           break;
       case 3:
           if(direction==1)
           image("land_elite_unit_right.png");  // 이미지 파일을 초기화
           if (direction == -1)
               image("land_elite_unit_left.png");  // 이미지 파일을 초기화
           missileDirection = sf::Vector2f(-1, 1);
           break;
       default:
           std::cout << "적군 생성자 오류" << std::endl;
           missileDirection = sf::Vector2f(0, 0);
           break;
       }
    }
   

    // - 공격
    // 생성
    void special_attack();
    // 업데이트
   /* void collision() {

    }*/
    void updateAttack();
    // 그리기
    void renderAttack(sf::RenderWindow& window);
    void deleteThisProjectile();
    
    bool missileLaunched;


private:
    std::vector<Missile*> missiles;
    sf::Vector2f missileDirection;

};
