#pragma once
#include "Character.h"
#include "Missile.h"
//#include <memory>
#include <iostream>

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position);


    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window);



    void image(const std::string& textureFile);

    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트


};

class NormalUnit : public Enemy {

public:
    NormalUnit(int stageNumber) : Enemy(100.0f, 1.0f, sf::Vector2f(0,0)) {
        image("sky_enemy_unit.png");  // 이미지 파일을 초기화
    }



};

class EliteUnit : public Enemy {

public:
    EliteUnit(int stageNumber) : Enemy(300.0f, 1.5f, sf::Vector2f(0, 0)) {
        image("sky_elite_unit.png");  // 이미지 파일을 초기화
        missileLaunched = false;
        // 위에 다 스위치로 처리
       switch (stageNumber) {
       case 1:
           missileDirection = sf::Vector2f(0, 1);
           break;
       case 2:
           missileDirection = sf::Vector2f(-1, 0);
           break;
       case 3:
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
    void updateAttack();
    // 그리기
    void renderAttack(sf::RenderWindow& window);
    
    
    bool missileLaunched;


private:
    std::vector<Missile> missiles;
    sf::Vector2f missileDirection;

};
