#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed)
    : position(startPosition), direction(direction), speed(speed) {
    shape.setRadius(5.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);
}

void Projectile::adjustDirection(){
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