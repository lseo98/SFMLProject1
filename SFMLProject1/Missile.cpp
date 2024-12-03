#include "Missile.h"

Missile::Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : Projectile(startPosition, direction, speed) { 
    damage = 200.0f;
    baseDamage = 200.0f;
    range = 200.0f;
    shape.setRadius(15.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);
}

void Missile::update() {
    adjustDirection(); 
    
    position += direction * speed;
    shape.setPosition(position);

    updateDamage();
}

/*void Missile::update(const sf::Vector2f& targetPosition) {
    if (isTracking) {
        sf::Vector2f updatedDirection = targetPosition - position;
        float magnitude = std::sqrt(updatedDirection.x * updatedDirection.x + updatedDirection.y * updatedDirection.y);
        if (magnitude != 0) {
            updatedDirection /= magnitude;
        }

        direction = direction*(0.3f)+(updatedDirection)*0.7f;

        if (std::abs(position.x - targetPosition.x) < 5.0f &&
            std::abs(position.y - targetPosition.y) < 5.0f) {
            isTracking = false;
        }
    }

    position += direction * speed;
    shape.setPosition(position);
    updateDamage();
}*/

void Missile::update(const sf::Vector2f& targetPosition) {
    if (isTracking) {
        // 목표 방향 계산
        sf::Vector2f updatedDirection = targetPosition - position;
        float magnitude = std::sqrt(updatedDirection.x * updatedDirection.x + updatedDirection.y * updatedDirection.y);
        if (magnitude != 0) {
            updatedDirection /= magnitude; // 정규화
        }

        // 기존 방향과 목표 방향 간의 각도를 제한
        float maxAngle = 0.03f; // 최대 회전 각도(라디안)
        float angleBetween = std::atan2(updatedDirection.y, updatedDirection.x) - std::atan2(direction.y, direction.x);

        // -π ~ π 범위로 각도를 정규화
        if (angleBetween > 3.14159f) {
            angleBetween -= 2.0f * 3.14159f;
        }
        if (angleBetween < -3.14159f) {
            angleBetween += 2.0f * 3.14159f;
        }

        // 각도 제한 적용
        if (angleBetween > maxAngle) {
            angleBetween = maxAngle;
        }
        if (angleBetween < -maxAngle) {
            angleBetween = -maxAngle;
        }

        // 새로운 방향 계산
        float newAngle = std::atan2(direction.y, direction.x) + angleBetween;
        direction.x = std::cos(newAngle);
        direction.y = std::sin(newAngle);

        // 목표에 도달하면 추적 종료
        if (std::abs(position.x - targetPosition.x) < 5.0f &&
            std::abs(position.y - targetPosition.y) < 5.0f) {
            isTracking = false;
        }
    }

    // 위치 업데이트
    position += direction * speed;
    shape.setPosition(position);
    updateDamage();
}


void Missile::draw(sf::RenderWindow& window) { 
    window.draw(shape);
}

void Missile::setTarget() {
    isTracking = true; // 추적 활성화
}