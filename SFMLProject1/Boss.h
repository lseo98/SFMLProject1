#pragma once
#include "Enemy.h"
#include <memory>
#include "Player.h"

class Boss : public Enemy {
public:
    Boss();
    void initBoss();
    void change_phase();               // ü�¿� ���� ����� �����ϴ� �޼���


    void attack(float deltaTime, Player& player, std::vector<std::unique_ptr<Missile>>& bossMissiles);
    void updateAttack(float deltaTime, Player& player, std::vector<std::unique_ptr<Missile>>& bossMissiles);

    void render(sf::RenderWindow& window, std::vector<std::unique_ptr<Missile>>& bossMissiles);

    Player* player; // �÷��̾� ��ü�� ���� ������
    int stageNumber;               // ���� �������� ��ȣ



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

    // ���� 1 ���� ����
    sf::Texture missileTexture;
    int maxMissile, launchedMissile;

    // ���� 2 ���� ����
    std::vector<sf::RectangleShape*> lasers;    // ������ �簢�� shape
    bool pattern2LaserVisible;                  // ������ ǥ�� ����

    // ���� 3 ���� ����, �Լ�
    sf::RectangleShape barrier;  // ���� �׷��� �� ��ġ�� ��Ÿ���� SFML RectangleShape
    bool barrierActive;          // �� Ȱ��ȭ ���θ� ��Ÿ���� �÷���
    bool barrierVisible;            // ���� ���� ���̴� �������� ����
    sf::Clock barrierBlinkClock;    // �� �������� ������ Ÿ�̸�
    float blinkInterval = 0.2f;     // ���� �����̴� ���� (�� ����)
    void barrierCollision(Player& player); // �÷��̾��� �߻�ü���� �浹ó��

    // ���� 4 ���� ����, �Լ�
    std::vector<HealUnit*> healUnits;                           // �� ���� ��ü
    int maxHealUnit, spawnHealUnitCount, killHealUnitCount;     // �� ���� ���� ī��Ʈ ���� // ���ʺ��� ������ ���ּ�, ������ ���� ��, ���� ���ǿ� ���� ������ ���� ��
    void deleteCollsionHealUnit();                              // �� ���� ���� ���� �˻� �� ���� �Լ�

    // ���� 5 ���� ����
    Shield shield;  // ���� ��ü
    bool shieldActive;  // ���� Ȱ�� ����

    // ���Ϻ� �Լ� 5��
    void pattern1_BossMissile(sf::Vector2f playerPosition, std::vector<std::unique_ptr<Missile>>& bossMissiles); // �����̻���
    void pattern2_Laser();
    void pattern3_Barrier(); // �� ��ġ
    void pattern4_Heal();
    void pattern5_DeployShield(); // ���շ� ��ġ



};