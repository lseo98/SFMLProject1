#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SeaEliteAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sea Stage: Á¤¿¹ À¯´Ö - ÃÑ¾Ë °ø°Ý\n";
    }
};
