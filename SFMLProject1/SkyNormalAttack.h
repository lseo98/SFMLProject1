#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SkyNormalAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sky Stage: �Ϲ� ���� - ���� ����\n";
    }
};
