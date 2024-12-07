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
    void collision(Player& player);

    void image(const std::string& textureFile, const sf::IntRect& textureRect = sf::IntRect());

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
    float previousY = 0.0f; // 이전 프레임의 Y 좌표
    float previousX = 1400.0f; // 이전 프레임의 X 좌표

    // 각 유닛들 생성 시 채력
   // static constexpr는 컴파일 타임 상수, static const는 상수
    static constexpr float maxHealth_NormalUnit = 100.0f;
    static constexpr float maxHealth_EliteUnit = 300.0f;
    static constexpr float maxHealth_HealUnit = 200.0f;
    static constexpr float maxHealth_Shield = 1000.0f;

    bool collisionFlag;

};

class NormalUnit : public Enemy {

public:
    //float maxHealth_NormalUnit;
    NormalUnit(int stageNumber, sf::Vector2f position,int direction)
        : Enemy(maxHealth_NormalUnit, 1.0f, position, stageNumber) {
        this->direction = direction; // 방향 설정
        sf::IntRect textureRect;  // 표시할 텍스처 영역
        if (stageNumber == 3 || stageNumber == 4) { // 땅 스테이지
            if (direction == -1) {
                textureRect = sf::IntRect(133, 0, 935, 530);
                image("land_enemy_unit.png", textureRect);
            }
            if (direction == 1) {
                textureRect = sf::IntRect(0, 0, 804, 530);
                image("land_enemy_unit_right.png", textureRect);
            }
        }
        else {
            textureRect = (stageNumber == 1 ? sf::IntRect(190, 220, 747, 656) :
                sf::IntRect(145, 213, 700, 515));
            image(stageNumber == 1 ? "sky_enemy_unit.png" :
                "sea_enemy_unit_b.png", textureRect);
        }
    } 
};

class EliteUnit : public Enemy {

public:
    // void fireMissile(sf::Vector2f targetPosition, std::vector<std::unique_ptr<Missile>>& globalMissiles);
    
    EliteUnit(int stageNumber, sf::Vector2f position,int direction)
        : Enemy(maxHealth_EliteUnit, 1.5f, position, stageNumber) {
        
        previousY = position.y;

        this->direction = direction; // 방향 설정
        // 위에 다 스위치로 처리
        sf::IntRect textureRect;  // 표시할 텍스처 영역
       switch (stageNumber) {
       case 1:
           // 이미지 전체 사용
           textureRect = sf::IntRect(5, 75, 650, 650);
           image("sky_elite_unit.png", textureRect);  // 이미지 파일을 초기화
           missileDirection = sf::Vector2f(0, 1);
           break;
       case 2:
           // 이미지의 특정 부분 사용
           textureRect = sf::IntRect(76, 292, 990, 630);
           image("sea_elite_unit.png", textureRect);  // 이미지 파일을 초기화
           missileDirection = sf::Vector2f(-1, 0);
           break;
       case 3:
       case 4:
           if (direction == 1) {
               textureRect = sf::IntRect(200, 0, 800, 435);
               image("land_elite_unit_right.png", textureRect);  // 이미지 파일을 초기화
           }
           if (direction == -1) {
               textureRect = sf::IntRect(0, 0, 800, 435);
               image("land_elite_unit_left.png", textureRect);  // 이미지 파일을 초기화
           }
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
    void fireMissile(sf::Vector2f targetPosition, std::vector<std::unique_ptr<Missile>>& globalMissiles);
    // 업데이트
   /* void collision() {

    }*/
    void updateAttack(float deltaTime);
 
    // 그리기
    void renderAttack(sf::RenderWindow& window);
    void deleteThisProjectile();
    
    bool missileLaunched;
    static void initializeTextures(); // static으로 선언


private:
    std::vector<std::unique_ptr<Missile>> missiles;
    sf::Vector2f missileDirection;
    static sf::Texture missileTexture;
    sf::Clock fireClock;           // 미사일 발사 간격 관리

    static sf::Texture missileTextures[3]; // 스테이지마다 다른 텍스처를 위한 배열
};

// 보스 패턴 4 관련 변수
class HealUnit : public Enemy {
public:
    HealUnit() : Enemy(maxHealth_HealUnit, 1.0f, sf::Vector2f(WINDOWWIDTH / 4 + 50, 200), 4) {
        this->direction = 1;    // 우측 이동
        image("land_elite_unit_right.png");  // 이미지 삽입
        //this->setPosition(sf::Vector2f(WINDOWWIDTH / 4+50, 200));
        //setPosition(sf::Vector2f(WINDOWWIDTH / 4+50, 200));
    }
};

// 보스 패턴 5 관련 변수
class Shield : public Enemy {
public:
    Shield() : Enemy(maxHealth_Shield, 0.0f, sf::Vector2f(WINDOWWIDTH / 2 - 50, WINDOWHEIGHT - 200), 4) {
        image("land_elite_unit_left.png"); // 이미지 삽입
    }
};
