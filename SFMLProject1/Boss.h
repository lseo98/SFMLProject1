#pragma once
#include "Enemy.h"
#include <memory>

class Boss : public Enemy {
public:
    Boss();
    void attack();            // ������ ���� ����
    void change_phase();               // ü�¿� ���� ����� �����ϴ� �޼���
    void execute_special_attack();     // ������ Ư�� ����

private:
    int phase;                         // ������ ������ ���¸� ��Ÿ���� ����
};
