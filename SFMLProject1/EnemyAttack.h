#pragma once

enum class AttackType {
    Normal,
    Elite
};

class EnemyAttack {
public:
    EnemyAttack(AttackType type) : attackType(type) {};
    virtual ~EnemyAttack() = default;

    virtual void attack_pattern() = 0;

protected:
    AttackType attackType;
};
