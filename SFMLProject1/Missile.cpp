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
        // ��ǥ ���� ���
        sf::Vector2f updatedDirection = targetPosition - position;
        float magnitude = std::sqrt(updatedDirection.x * updatedDirection.x + updatedDirection.y * updatedDirection.y);
        if (magnitude != 0) {
            updatedDirection /= magnitude; // ����ȭ
        }

        // ���� ����� ��ǥ ���� ���� ������ ����
        float maxAngle = 0.03f; // �ִ� ȸ�� ����(����)
        float angleBetween = std::atan2(updatedDirection.y, updatedDirection.x) - std::atan2(direction.y, direction.x);

        // -�� ~ �� ������ ������ ����ȭ
        if (angleBetween > 3.14159f) {
            angleBetween -= 2.0f * 3.14159f;
        }
        if (angleBetween < -3.14159f) {
            angleBetween += 2.0f * 3.14159f;
        }

        // ���� ���� ����
        if (angleBetween > maxAngle) {
            angleBetween = maxAngle;
        }
        if (angleBetween < -maxAngle) {
            angleBetween = -maxAngle;
        }

        // ���ο� ���� ���
        float newAngle = std::atan2(direction.y, direction.x) + angleBetween;
        direction.x = std::cos(newAngle);
        direction.y = std::sin(newAngle);

        // ��ǥ�� �����ϸ� ���� ����
        if (std::abs(position.x - targetPosition.x) < 5.0f &&
            std::abs(position.y - targetPosition.y) < 5.0f) {
            isTracking = false;
        }
    }

    // ��ġ ������Ʈ
    position += direction * speed;
    shape.setPosition(position);
    updateDamage();
}


void Missile::draw(sf::RenderWindow& window) { 
    window.draw(shape);
}

void Missile::setTarget() {
    isTracking = true; // ���� Ȱ��ȭ
}