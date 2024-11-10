#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed); // �⺻ ������ ����
    virtual ~Projectile() = default;

    virtual void update() = 0;           // ��ġ ������Ʈ
    virtual void draw(sf::RenderWindow& window) = 0; // ȭ�鿡 �׸���
    virtual bool isOffScreen(int screenWidth, int screenHeight) const = 0; // ȭ�� ������ �������� Ȯ��

    void adjustDirection(); // ������ ������ �����ϴ� �޼���

protected:
    sf::Vector2f position;   // ���� ��ġ
    sf::Vector2f direction;  // �̵� ����
    float speed;             // �̵� �ӵ�
    sf::CircleShape shape;   // SFML���� ����� �⺻ ���� (��: ���� ���)
};
