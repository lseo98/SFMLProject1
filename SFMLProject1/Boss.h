#pragma once
#include "Enemy.h"
#include <memory>

class Boss : public Enemy {
public:
    Boss(); 
    void change_phase();               // ü�¿� ���� ����� �����ϴ� �޼���
 

    void updateAttack(float deltaTime);

  



private:
    int phase;                         // ������ ������ ���¸� ��Ÿ���� ����
    float dt;
    float time;
    float pattern1;
    float pattern2;
    float pattern3;
    float pattern4;
    float pattern5;

    // ���Ϻ� �Լ� 5��






};
