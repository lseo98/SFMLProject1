#pragma once
#include "Character.h"
#include "AttackStrategy.h"
#include <memory>
#include "Projectile.h"

class Player : public Character {
public:
    Player();

    void move(sf::Vector2f updatePosition);
    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window) override; 

    void basic_attack();
    void special_attack();
    void ultimate_attack();

    void setAttackStrategy(std::unique_ptr<AttackStrategy> attackStrategy);
    AttackStrategy* getAttackStrategy() const { return attackStrategy.get(); } // 현재 공격 전략 반환

    void performBasicAttack();      // 기본 공격 수행
    void performSpecialAttack();    // 특수 공격 수행 추가

    std::vector<std::unique_ptr<Projectile>> projectiles; // 발사체 벡터

    float power = 150.0f;

private:
    std::unique_ptr<AttackStrategy> attackStrategy;
};
