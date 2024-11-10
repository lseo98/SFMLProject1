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

bool AntiTankMissile::isOffScreen(int screenWidth, int screenHeight) const {
    sf::Vector2f pos = shape.getPosition();
    return (pos.x < 0 || pos.x > screenWidth || pos.y < 0 || pos.y > screenHeight); // ȭ�� �� Ȯ��
}
