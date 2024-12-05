#pragma once
#include "Projectile.h"

class Missile : public Projectile {
public:
    Missile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed);

    void update() override;
    void update(const sf::Vector2f& targetPosition); // ���� �̻��� ������Ʈ

    void draw(sf::RenderWindow& window) override;
    float getRange() { return range; }

    void setTexture(const sf::Texture& texture, const sf::IntRect& textureRect);
    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;

    void changeRange(float range) { this->range = range; }

    void setTarget();


private:
    float range;
    sf::Vector2f* targetPosition = nullptr; // �÷��̾� ��ġ ����
    bool isTracking = false;                // ���� ����
};
