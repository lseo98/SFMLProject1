#pragma once
#include "AttackStrategy.h"
#include <iostream>

class SkyAttackStrategy : public AttackStrategy {
public:
    void basic_attack() override {
        std::cout << "Sky Stage: �⺻ ���� - �Ѿ� �߻�\n";
    }

    void special_attack() override {
        std::cout << "Sky Stage: Ư�� ���� - ���� �̻��� �߻�\n";
    }

    void ultimate_attack() override {
        std::cout << "Sky Stage: �ʻ�� - �Ʊ� ����� ���� ����\n";
    }
};
