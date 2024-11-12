#include "AntiTankMissile.h"

AntiTankMissile::AntiTankMissile(const sf::Vector2f& startPosition)
    : Projectile(startPosition, sf::Vector2f(0.0f, -1.0f), 8.0f) { // ���� ����, �ӵ� 8.0f
    shape.setRadius(10.0f);            // �̻��� ũ�� ����
    shape.setFillColor(sf::Color::Yellow); // �̻��� ���� ����
    shape.setPosition(position);        // ���� ��ġ ����
}

void AntiTankMissile::update() {
    adjustDirection();
    position += direction * speed;
    shape.setPosition(position); // ��ġ ������Ʈ
}

void AntiTankMissile::draw(sf::RenderWindow& window) {
    window.draw(shape); // â�� �׸���
}
