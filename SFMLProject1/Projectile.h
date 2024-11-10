#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed); // 기본 생성자 제거
    virtual ~Projectile() = default;

    virtual void update() = 0;           // 위치 업데이트
    virtual void draw(sf::RenderWindow& window) = 0; // 화면에 그리기
    virtual bool isOffScreen(int screenWidth, int screenHeight) const = 0; // 화면 밖으로 나갔는지 확인

    void adjustDirection(); // 방향을 각도로 조정하는 메서드

protected:
    sf::Vector2f position;   // 현재 위치
    sf::Vector2f direction;  // 이동 방향
    float speed;             // 이동 속도
    sf::CircleShape shape;   // SFML에서 사용할 기본 도형 (예: 원형 모양)
};
