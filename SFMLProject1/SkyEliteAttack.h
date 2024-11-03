#pragma once
#include "EnemyAttackPattern.h"
#include <iostream>

class SkyEliteAttack : public EnemyAttackPattern {
public:
    void attack_pattern() override {
        std::cout << "Sky Stage: Á¤¿¹ À¯´Ö - µ¹Áø & ÃÑ¾Ë °ø°Ý\n";
    }
};
