#pragma once
#include "Character.h"

//#include <memory>
#include <iostream>
#include "Projectile.h"
#include "Missile.h"
#include "Bullet.h"

class Player : public Character {
public:
    Player();
    

    float power = 150.0f;

    void move(sf::Vector2f updatePosition);
    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window) override; 
    void updateDirection(char direction,int stageNum); // 유닛 방향 설정
    void image(std::string textureFile);
    
    // 스테이지 전환시 플레이어 세팅
    void setPlayer(int stageNumber);  
    
   

    // - 공격
    // 생성
    void basic_attack();
    void special_attack();
    void ultimate_attack();
    // 업데이트
    void updateAttack();
    // 그리기
    void renderAttack(sf::RenderWindow& window);
    

    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트

    bool missileLaunched;

private:

    std::vector<Bullet> bullets;
    std::vector<Missile> missiles;
    sf::Vector2f bulletDirection; // 기본 공격 방향  
    sf::Vector2f missileDirection;
    char direction;
};
