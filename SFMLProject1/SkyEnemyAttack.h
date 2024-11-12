#pragma once
#include "EnemyAttack.h"
#include <iostream>

class SkyEnemyAttack : public EnemyAttack {
public:
    SkyEnemyAttack(AttackType type) : EnemyAttack(type) {}

    void attack_pattern() override {
        if (attackType == AttackType::Normal) {
            std::cout << "Sky Normal Attack\n";
        }
        else {
            std::cout << "Sky Elite Attack\n";
        }
    }
};