#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class LandNormalAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Land Stage: �Ϲ� ���� - �浹 ����\n";
    }
};
