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
   
    void crashed() { isCrashed = true; }
    bool checkCrashed() { return isCrashed; }

    void adjustDirection(); // ������ ������ �����ϴ� �޼���
    
    void changeDamage(float damage) { this->damage = damage; }
    float getDamage() { return damage; }

    
    bool isAlly; // �Ʊ� ���� �߻�ü ����

    sf::Vector2f position;   // ���� ��ġ
protected:
    sf::Vector2f direction;  // �̵� ����
    float speed;             // �̵� �ӵ�
    sf::CircleShape shape;   // SFML���� ����� �⺻ ���� (��: ���� ���)
    float damage;            // ����ü�� ���ݷ�
    bool isCrashed;          // ����ü�� �浹�� �Ͼ�ٸ� true / ���� �� false
};
