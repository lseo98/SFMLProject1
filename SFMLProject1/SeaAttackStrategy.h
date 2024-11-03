#pragma once
#include "AttackStrategy.h"
#include <iostream>

class SeaAttackStrategy : public AttackStrategy {
public:
    void basic_attack() override {
        std::cout << "Sea Stage: �⺻ ���� - ���ӿ��� �߻�Ǵ� �Ѿ�\n";
    }

    void special_attack() override {
        std::cout << "Sea Stage: Ư�� ���� - ��� �߻�\n";
    }

    void ultimate_attack() override {
        std::cout << "Sea Stage: �ʻ�� - ��Ը� ��� ����\n";
    }
};
