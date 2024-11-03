#pragma once
#include "AttackStrategy.h"
#include <iostream>

class LandAttackStrategy : public AttackStrategy {
public:
    void basic_attack() override {
        std::cout << "Land Stage: 기본 공격 - 총알 발사\n";
    }

    void special_attack() override {
        std::cout << "Land Stage: 특수 공격 - 대전차 미사일 발사\n";
    }

    void ultimate_attack() override {
        std::cout << "Land Stage: 필살기 - 폭탄 떨구기\n";
    }
};
