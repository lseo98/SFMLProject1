#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SeaNormalAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sea Stage: 일반 유닛 - 충돌 공격\n";
    }
};
