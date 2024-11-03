#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SkyNormalAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sky Stage: 일반 유닛 - 돌진 공격\n";
    }
};
