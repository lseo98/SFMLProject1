#include "Boss.h"
#include <iostream>

Boss::Boss() : Enemy(3000.0f, 0.5f), phase(1) {
    // 보스의 초기 체력은 3000, 속도는 0.5로 설정
}

void Boss::attack() {
    std::cout << "기본 공격, 현재 페이즈: " << phase << "\n";
    // 보스의 기본 공격
}

void Boss::change_phase() {
    if (health < 1500.0f && phase == 1) {
        phase = 2;
        std::cout << "페이즈 2로 전환\n";
    }
    else if (health < 500.0f && phase == 2) {
        phase = 3;
        std::cout << "페이즈 3으로 전환\n";
    }
    // 체력에 따라 보스의 페이즈 변경
}

void Boss::execute_special_attack() {
    std::cout << "특수 공격\n";
}
