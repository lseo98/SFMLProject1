#pragma once
#include "Enemy.h"
#include <memory>
#include "Player.h"

class Boss : public Enemy {
public:
    Boss();
    void change_phase();               // ü�¿� ���� ����� �����ϴ� �޼���


    void attack(float deltaTime);
    void updateAttack(float deltaTime, Player& player);

    void render(sf::RenderWindow& window);

private:
    int phase;                                 // ������ ������ ���¸� ��Ÿ���� ����
    int attackPattern;                         // ������ ���� ������ �����ϴ� ����
    int beforeAttackpattern;                   // ������ ���� ���� ����

    // �ð� ���� ����
    float dt;
    float time;
    float pattern1;
    float pattern2;
    float pattern3;
    float pattern4;
    float pattern5;


    // ���� 2 ���� ����
    std::vector<sf::RectangleShape*> lasers;    // ������ �簢�� shape
    bool pattern2LaserVisible;                  // ������ ǥ�� ����


    // ���� 4 ���� ����

    std::vector<HealUnit*> healUnits;                           // �� ���� ��ü
    int maxHealUnit, spawnHealUnitCount, killHealUnitCount;     // �� ���� ���� ī��Ʈ ���� // ���ʺ��� ������ ���ּ�, ������ ���� ��, ���� ���ǿ� ���� ������ ���� ��
    void deleteCollsionHealUnit();                              // �� ���� ���� ���� �˻� �� ���� �Լ�

    // ���Ϻ� �Լ� 5��

    void pattern2_Laser();

    void pattern4_Heal();




};