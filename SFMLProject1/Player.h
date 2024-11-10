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
    AttackStrategy* getAttackStrategy() const { return attackStrategy.get(); } // ���� ���� ���� ��ȯ

    void performBasicAttack();      // �⺻ ���� ����
    void performSpecialAttack();    // Ư�� ���� ���� �߰�

    std::vector<std::unique_ptr<Projectile>> projectiles; // �߻�ü ����

    float power = 150.0f;

private:
    std::unique_ptr<AttackStrategy> attackStrategy;
};
