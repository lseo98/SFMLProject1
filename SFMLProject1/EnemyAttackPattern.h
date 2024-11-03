#pragma once

class EnemyAttackPattern {
public:
    virtual ~EnemyAttackPattern() = default;
    virtual void attack_pattern() = 0;
};
