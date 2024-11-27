#pragma once
#include "Enemy.h"
#include <memory>

class Boss : public Enemy {
public:
    Boss();
    void attack();            // 보스의 공격 패턴
    void change_phase();               // 체력에 따라 페이즈를 변경하는 메서드
    void execute_special_attack();     // 보스의 특수 공격

private:
    int phase;                         // 보스의 페이즈 상태를 나타내는 변수
};
