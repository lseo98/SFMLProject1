#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SeaEliteAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sea Stage: ���� ���� - �Ѿ� ����\n";
    }
};
