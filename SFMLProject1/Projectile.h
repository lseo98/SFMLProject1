#pragma once
#include <SFML/Graphics.hpp>

extern int WINDOWWIDTH, WINDOWHEIGHT;

class Projectile {
public:
    Projectile(sf::Vector2f startPosition, sf::Vector2f direction, float speed); // 기본 생성자 제거
    virtual ~Projectile() = default;

    virtual void update() = 0;           // 위치 업데이트
    virtual void draw(sf::RenderWindow& window) = 0; // 화면에 그리기
    bool isOffScreen() const; // 중앙 900x900 범위를 기준으로 화면 밖으로 나갔는지 확인
   
    void crashed() { isCrashed = true; }
    bool checkCrashed() { return isCrashed; }

    void adjustDirection(); // 방향을 각도로 조정하는 메서드
    
    void changeDamage(float damage) { this->damage = damage; }
    float getDamage() { return damage; }

    
    bool isAlly; // 아군 유닛 발사체 여부

    sf::Vector2f position;   // 현재 위치
protected:
    sf::Vector2f direction;  // 이동 방향
    float speed;             // 이동 속도
    sf::CircleShape shape;   // SFML에서 사용할 기본 도형 (예: 원형 모양)
    float damage;            // 공격체의 공격력
    bool isCrashed;          // 공격체가 충돌이 일어났다면 true / 생성 시 false
};
