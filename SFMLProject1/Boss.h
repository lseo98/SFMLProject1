#pragma once
#include "Enemy.h"
#include <memory>

class Boss : public Enemy {
public:
    Boss(); 
    void change_phase();               // ü�¿� ���� ����� �����ϴ� �޼���
 

    void attack(float deltaTime);
    void updateAttack(float deltaTime);

    void render(sf::RenderWindow& window);

private:
    int phase;                         // ������ ������ ���¸� ��Ÿ���� ����
    
    // �ð� ���� ����
    float dt;
    float time;
    float pattern1;
    float pattern2;
    float pattern3;
    float pattern4;
    float pattern5;


    // ���� 2 ���� ����
    std::vector<sf::RectangleShape*> laser;

    // ���Ϻ� �Լ� 5��

    void pattern2_Laser();




};
