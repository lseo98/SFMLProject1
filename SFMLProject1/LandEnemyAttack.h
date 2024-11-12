#pragma once
#include "EnemyAttack.h"
#include <iostream>

class LandEnemyAttack : public EnemyAttack {
public:
    LandEnemyAttack(AttackType type) : EnemyAttack(type) {}

    void attack_pattern() override {
        if (attackType == AttackType::Normal) {
            std::cout << "Land Normal Attack\n";
        }
        else {
            std::cout << "Land Elite Attack\n";
        }
    }
};
