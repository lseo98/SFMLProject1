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
    void basicAttack();
    void specialAttack();
    void ultimateAttack();
    // 업데이트
    void updateAttack();
    void updateAllies(float delatime);
    // 그리기
    void renderAttack(sf::RenderWindow& window);
    void drawAllies(sf::RenderWindow& window);  // 아군 유닛 그리기 메서드 추가
    void allyAttack();

    // 쿨타임 전용 업데이트 메서드 추가
    void updateCooldowns(float dt);  // 쿨타임 업데이트 (특수공격과 필살기 모두 포함)
    

    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트

    //bool missileLaunched;

private:

    std::vector<Bullet> bullets;
    std::vector<Missile> missiles;
    std::vector<Missile> allyMissiles;    // 아군 유닛들이 발사한 미사일 벡터

    sf::Vector2f bulletDirection; // 기본 공격 방향  
    sf::Vector2f missileDirection;
    char direction;

    // 특수 공격 쿨타임 관련 변수
    float specialAttackCooldown;    // 특수 공격 쿨타임 (초 단위)
    float timeSinceLastSpecial;     // 마지막 특수 공격 이후 경과 시간
    bool canSpecialAttack;          // 특수 공격 가능 여부

    // 필살기 쿨타임 관련 변수
    float ultimateAttackCooldown;   // 필살기 쿨타임 (초 단위)
    float timeSinceLastUltimate;    // 마지막 필살기 이후 경과 시간
    bool canUltimateAttack;         // 필살기 가능 여부

    // 필살기 아군 유닛 멤버 변수
    std::vector<sf::Sprite> allyUnits; // 아군 유닛들을 저장하는 멤버 변수
    sf::Texture allyTexture;           // 아군 유닛의 텍스처

    float waitTime;  // 하늘 스테이지에서 아군 유닛의 대기 시간
};
