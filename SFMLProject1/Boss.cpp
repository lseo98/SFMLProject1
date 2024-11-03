#include "Boss.h"
#include <iostream>

Boss::Boss() : Enemy(3000.0f, 0.5f), phase(1) {
    // ������ �ʱ� ü���� 3000, �ӵ��� 0.5�� ����
}

void Boss::attack() {
    std::cout << "�⺻ ����, ���� ������: " << phase << "\n";
    // ������ �⺻ ����
}

void Boss::change_phase() {
    if (health < 1500.0f && phase == 1) {
        phase = 2;
        std::cout << "������ 2�� ��ȯ\n";
    }
    else if (health < 500.0f && phase == 2) {
        phase = 3;
        std::cout << "������ 3���� ��ȯ\n";
    }
    // ü�¿� ���� ������ ������ ����
}

void Boss::execute_special_attack() {
    std::cout << "Ư�� ����\n";
}
