#pragma once
#include "AttackStrategy.h"
#include <iostream>

class SkyAttackStrategy : public AttackStrategy {
public:
    void basic_attack() override {
        std::cout << "Sky Stage: 기본 공격 - 총알 발사\n";
    }

    void special_attack() override {
        std::cout << "Sky Stage: 특수 공격 - 유도 미사일 발사\n";
    }

    void ultimate_attack() override {
        std::cout << "Sky Stage: 필살기 - 아군 비행기 지원 공격\n";
    }
};
