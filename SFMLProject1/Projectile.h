#pragma once
#include <SFML/Graphics.hpp>

extern int WINDOWWIDTH, WINDOWHEIGHT;

class Projectile {
public:
    Projectile(sf::Vector2f startPosition, sf::Vector2f direction, float speed); // �⺻ ������ ����
    virtual ~Projectile() = default;

    // Getter �Լ�
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getDirection() const { return direction; }
    float getSpeed() const { return speed; }

    // Setter �Լ�
    void setPosition(const sf::Vector2f& newPosition) { position = newPosition; }
    void setDirection(const sf::Vector2f& newDirection) { direction = newDirection; }
    void setSpeed(float newSpeed) { speed = newSpeed; }

    virtual void update() = 0;           // ��ġ ������Ʈ
    virtual void draw(sf::RenderWindow& window) = 0; // ȭ�鿡 �׸���
    bool isOffScreen() const; // �߾� 900x900 ������ �������� ȭ�� ������ �������� Ȯ��
   
    void crashed() { isCrashed = true; }
    bool checkCrashed() { return isCrashed; }

    void adjustDirection(); // ������ ������ �����ϴ� �޼���

    void updateDamage();

    void initializeClock() {
        lifetimeClock.restart(); // ��� �ð� �ʱ�ȭ
    }

    
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
    float baseDamage;    // �ʱ� ������ ����
    sf::Clock lifetimeClock; // �߻�ü�� ��� �ð� ����
};
