#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : position(startPosition), direction(direction), speed(speed) {
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);
}

void Projectile::adjustDirection(){
    float angle = 0.0f; // 초기 각도 설정

    // 화살표 입력 확인
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angle = -3.0f; // 왼쪽으로 3도 회전
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angle = 3.0f; // 오른쪽으로 3도 회전
    }

    // 화살표 키가 눌리지 않았다면 회전하지 않음
    if (angle == 0.0f) return;

    // 회전 각도를 라디안으로 변환
    float radian = angle * 3.14159265f / 180.0f;

    // 새로운 방향 벡터 계산 (회전 행렬 사용)
    float newX = direction.x * cos(radian) - direction.y * sin(radian);
    float newY = direction.x * sin(radian) + direction.y * cos(radian);
    direction = sf::Vector2f(newX, newY);
}