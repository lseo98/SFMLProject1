#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SeaNormalAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sea Stage: �Ϲ� ���� - �浹 ����\n";
    }
};
