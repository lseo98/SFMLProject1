#pragma once
#include "AttackStrategy.h"
#include <iostream>

class SeaAttackStrategy : public AttackStrategy {
public:
    void basic_attack() override {
        std::cout << "Sea Stage: 기본 공격 - 물속에서 발사되는 총알\n";
    }

    void special_attack() override {
        std::cout << "Sea Stage: 특수 공격 - 어뢰 발사\n";
    }

    void ultimate_attack() override {
        std::cout << "Sea Stage: 필살기 - 대규모 기뢰 폭발\n";
    }
};
