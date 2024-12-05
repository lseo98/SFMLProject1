#pragma once
#include "Character.h"
#include "Enemy.h" 
//#include <memory>
#include <iostream>
#include "Projectile.h"
#include "Missile.h"
#include "Bullet.h"
#include <vector>
class Player : public Character {
public:
    Player();
    

    float power = 150.0f;

    void move(sf::Vector2f updatePosition);
   // void takeDamage(float amount) override;
    void draw(sf::RenderWindow& window) override; 
    void updateDirection(char direction,int stageNum); // 유닛 방향 설정
    void image(std::string textureFile, const sf::IntRect& textureRect);
    void initializeHearts();

    // 스테이지 전환시 플레이어 세팅
    void setPlayer(int stageNumber);  

    void restart();
    
    sf::Texture heartTexture; // 하트 텍스처
    std::vector<sf::Sprite> hearts; // 하트를 표시할 스프라이트 배열
    void changeHeartSprite();

    // - 공격
    // 생성
    void basicAttack();
    void specialAttack();
    void ultimateAttack();
    // 업데이트
    void collision(std::vector<Enemy*>& enemies);    // 공격체-적 충돌 처리
    void enemyProjectileCollision(std::vector<std::unique_ptr<Missile>>& globalMissiles);    // 공격체-적 충돌 처리
    void deleteThisProjectile();                     // 충돌된 내 발사체 삭제
    void updateAttack();                             // 공격체 업데이트
    void updateAllies(float delatime, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Missile>>& globalMissiles);
    // 그리기
    void renderAttack(sf::RenderWindow& window);
    void drawAllies(sf::RenderWindow& window);  // 아군 유닛 그리기 메서드 추가
    void allyAttack();

    // 쿨타임 전용 업데이트 메서드 추가
    void updateCooldowns(float dt);  // 쿨타임 업데이트 (특수공격과 필살기 모두 포함)
    
    void countKillNormal() { this->killCountNomalUnit++; }
    void countKillElite() { this->killCountEliteUnit++; }


    sf::Texture texture;      // 이미지 텍스처
    sf::Sprite sprite;        // 텍스처를 사용할 스프라이트

    sf::Vector2f bulletStartPosition;

    // 궁극기 남은 쿨타임 반환 함수
    float getUltimateAttackRemainingCooldown() const;
    // 특수 공격 남은 쿨타임 반환 함수
    float getSpecialAttackRemainingCooldown() const;

    sf::Vector2f getPosition() const {
        return position; // 플레이어의 현재 위치를 반환
    }
    void takeDamage(float amount) override;
    // 깜빡임
    void triggerBlink();             // 깜빡임 시작
    void updateBlink();              // 깜빡임 상태 업데이트

    //bool missileLaunched;

private:

    std::vector<Bullet*> bullets;
    std::vector<Missile*> missiles;
    std::vector<Missile*> allyMissiles;    // 아군 유닛들이 발사한 미사일 벡터 

    sf::Vector2f bulletDirection; // 기본 공격 방향  
    sf::Vector2f missileDirection;
    char direction;

    // 특수 공격 쿨타임 관련 변수
    float specialAttackCooldown;    // 특수 공격 쿨타임 (초 단위)
    float timeSinceLastSpecial;     // 마지막 특수 공격 이후 경과 시간
    bool canSpecialAttack=true;          // 특수 공격 가능 여부

    // 필살기 쿨타임 관련 변수
    float ultimateAttackCooldown;   // 필살기 쿨타임 (초 단위)
    float timeSinceLastUltimate;    // 마지막 필살기 이후 경과 시간
    bool canUltimateAttack=true;         // 필살기 가능 여부

    // 필살기 아군 유닛 멤버 변수
    std::vector<sf::Sprite> allyUnits; // 아군 유닛들을 저장하는 멤버 변수
    sf::Texture allyTexture;           // 아군 유닛의 텍스처
    sf::Texture MissileTextures[3];   // 스테이지별 발사체 이미지 (1: 하늘, 2: 바다, 3: 땅) 
    sf::Texture AllMissileTextures[3];   // 스테이지별 발사체 이미지 (1: 하늘, 2: 바다, 3: 땅) 

    float waitTime;  // 하늘 스테이지에서 아군 유닛의 대기 시간

    sf::Texture bulletTextures[3];   // 스테이지별 발사체 이미지 (1: 하늘, 2: 바다, 3: 땅) 
    int stageNumber;                 // 현재 스테이지 번호
    void loadProjectileTextures();

    int killCountNomalUnit, killCountEliteUnit; // 처치한 적군 수

    // 깜빡임
    bool isBlinking = false;         // 깜빡임 상태
    sf::Clock blinkClock;            // 깜빡임 타이머
    float blinkDuration = 1.0f;      // 깜빡임 지속 시간 (초)
    float blinkInterval = 0.1f;      // 깜빡이는 간격 (0.1초마다 토글)
    bool isVisible = true;           // 현재 보이는 상태

    bool isOnGround = false; // 바닥 충돌 상태 플래그

};
