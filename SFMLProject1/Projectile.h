#pragma once
#include <SFML/Graphics.hpp>

extern int WINDOWWIDTH, WINDOWHEIGHT;

class Projectile {
public:
    Projectile(sf::Vector2f startPosition, sf::Vector2f direction, float speed); // �⺻ ������ ����
    virtual ~Projectile() = default;

    virtual void update() = 0;           // ��ġ ������Ʈ
    virtual void draw(sf::RenderWindow& window) = 0; // ȭ�鿡 �׸���
    bool isOffScreen() const; // �߾� 900x900 ������ �������� ȭ�� ������ �������� Ȯ��

    void adjustDirection(); // ������ ������ �����ϴ� �޼���

protected:
    sf::Vector2f position;   // ���� ��ġ
    sf::Vector2f direction;  // �̵� ����
    float speed;             // �̵� �ӵ�
    sf::CircleShape shape;   // SFML���� ����� �⺻ ���� (��: ���� ���)
};
