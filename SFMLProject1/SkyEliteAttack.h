#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SkyEliteAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sky Stage: ���� ���� - ���� & �Ѿ� ����\n";
    }
};
