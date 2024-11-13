#pragma once
#include "Character.h"
#include "PlayerAttack.h"
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

    void setPlayerAttack(std::unique_ptr<PlayerAttack> attackType);
    PlayerAttack* getAttackStrategy() const { return attackType.get(); } // ���� ���� ���� ��ȯ

    void performBasicAttack();      // �⺻ ���� ����
    void performSpecialAttack();    // Ư�� ���� ���� �߰�

    std::vector<std::unique_ptr<Projectile>> projectiles; // �߻�ü ����

    float power = 150.0f;

    void image(std::string);

    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ


private:
    std::unique_ptr<PlayerAttack> attackType;
};
