#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class LandEliteAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Land Stage: Á¤¿¹ À¯´Ö - ÃÑ¾Ë °ø°Ý\n";
    }
};
