#pragma once

class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;
    virtual void basic_attack() = 0;
    virtual void special_attack() = 0;
    virtual void ultimate_attack() = 0;
};
