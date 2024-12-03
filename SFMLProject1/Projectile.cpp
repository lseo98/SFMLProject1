#include "Projectile.h"
#include "Game.h"

Projectile::Projectile(sf::Vector2f startPosition, sf::Vector2f direction, float speed)
    : position(startPosition), direction(direction), speed(speed) {
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);
}

bool Projectile::isOffScreen() const {
    int centerX = WINDOWWIDTH / 2;
    int centerY = WINDOWHEIGHT / 2;
    int rangeX = 500;
    int rangeY = 500;

    return (position.x < centerX - rangeX || position.x > centerX + rangeX ||
        position.y < centerY - rangeY || position.y > centerY + rangeY);
}


void Projectile::adjustDirection(){
    if (isAlly) {
        // 필살기 아군 유닛 발사체인 경우 회전하지 않음
        return;
    }
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

void Projectile::updateDamage() {
    float elapsedTime = Game::globalClock.getElapsedTime().asSeconds(); // 경과 시간
    float minDamage = baseDamage * 0.7f; // 최소 데미지 (기본 데미지의 70%)

    // 데미지를 10초마다 1%씩 감소
    damage = std::max(baseDamage * std::pow(0.99f, elapsedTime / 10.0f), minDamage);
}