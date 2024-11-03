#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class LandNormalAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Land Stage: 일반 유닛 - 충돌 공격\n";
    }
};
