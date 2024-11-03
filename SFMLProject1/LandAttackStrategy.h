#pragma once
#include "AttackStrategy.h"
#include <iostream>

class LandAttackStrategy : public AttackStrategy {
public:
    void basic_attack() override {
        std::cout << "Land Stage: �⺻ ���� - �Ѿ� �߻�\n";
    }

    void special_attack() override {
        std::cout << "Land Stage: Ư�� ���� - ������ �̻��� �߻�\n";
    }

    void ultimate_attack() override {
        std::cout << "Land Stage: �ʻ�� - ��ź ������\n";
    }
};
