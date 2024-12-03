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
        // �ʻ�� �Ʊ� ���� �߻�ü�� ��� ȸ������ ����
        return;
    }
    float angle = 0.0f; // �ʱ� ���� ����

    // ȭ��ǥ �Է� Ȯ��
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angle = -3.0f; // �������� 3�� ȸ��
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angle = 3.0f; // ���������� 3�� ȸ��
    }

    // ȭ��ǥ Ű�� ������ �ʾҴٸ� ȸ������ ����
    if (angle == 0.0f) return;

    // ȸ�� ������ �������� ��ȯ
    float radian = angle * 3.14159265f / 180.0f;

    // ���ο� ���� ���� ��� (ȸ�� ��� ���)
    float newX = direction.x * cos(radian) - direction.y * sin(radian);
    float newY = direction.x * sin(radian) + direction.y * cos(radian);
    direction = sf::Vector2f(newX, newY);
}

void Projectile::updateDamage() {
    float elapsedTime = Game::globalClock.getElapsedTime().asSeconds(); // ��� �ð�
    float minDamage = baseDamage * 0.7f; // �ּ� ������ (�⺻ �������� 70%)

    // �������� 10�ʸ��� 1%�� ����
    damage = std::max(baseDamage * std::pow(0.99f, elapsedTime / 10.0f), minDamage);
}