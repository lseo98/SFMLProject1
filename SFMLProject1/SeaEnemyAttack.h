#pragma once
#include "EnemyAttack.h"
#include <iostream>

class SeaEnemyAttack : public EnemyAttack {
public:
    SeaEnemyAttack(AttackType type) : EnemyAttack(type) {}

    void attack_pattern() override {
        if (attackType == AttackType::Normal) {
            std::cout << "Sea Normal Attack\n";
        }
        else {
            std::cout << "Sea Elite Attack\n";
        }
    }
};
