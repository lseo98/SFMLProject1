#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class LandEliteAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Land Stage: ���� ���� - �Ѿ� ����\n";
    }
};
