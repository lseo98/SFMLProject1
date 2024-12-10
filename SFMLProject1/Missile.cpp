#include "Missile.h"
#include<iostream>

Missile::Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : Projectile(startPosition, direction, speed) { 
    damage = 200.0f;
    baseDamage = 200.0f;
    range = 200.0f;
}

void Missile::update() {
    adjustDirection(); 
    
    position += direction * speed;
    sprite.setPosition(position);
    float angleDegrees = atan2(direction.y, direction.x) * 180.0f / 3.14159265f + 90.0f;
    sprite.setRotation(angleDegrees);
    updateDamage();
}
void Missile::setTexture(const sf::Texture& texture, const sf::IntRect& textureRect) {
    sprite.setTexture(texture);
    if (textureRect != sf::IntRect()) {
        this->sprite.setTextureRect(textureRect);
    }
  
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(0.07f, 0.07f);
    sprite.setPosition(position);

}

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
        if (std::abs(position.x - targetPosition.x) < 150.0f &&
            std::abs(position.y - targetPosition.y) < 150.0f) {
            isTracking = false;
        }
        position += direction * speed;
        sprite.setPosition(position);
        float angleDegrees = atan2(direction.y, direction.x) * 180.0f / 3.14159265f + 90.0f;
        sprite.setRotation(angleDegrees);
    }
    else {
        position += direction * speed;
        sprite.setPosition(position);
    }
}


void Missile::draw(sf::RenderWindow& window) { 
    window.draw(sprite);
}

void Missile::setTarget() {
    isTracking = true; // ���� Ȱ��ȭ
}