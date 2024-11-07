#pragma once
#include "Character.h"
#include "AttackStrategy.h"
#include <memory>

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

    float power = 150.0f;

private:
    std::unique_ptr<AttackStrategy> attackStrategy;
};
