#pragma once
#include "Character.h"
#include "Missile.h"
//#include <memory>
#include <iostream>

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position);


    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window);



    void image(const std::string& textureFile);

    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ


};

class NormalUnit : public Enemy {

public:
    NormalUnit(int stageNumber) : Enemy(100.0f, 1.0f, sf::Vector2f(0,0)) {
        image("sky_enemy_unit.png");  // �̹��� ������ �ʱ�ȭ
    }



};

class EliteUnit : public Enemy {

public:
    EliteUnit(int stageNumber) : Enemy(300.0f, 1.5f, sf::Vector2f(0, 0)) {
        image("sky_elite_unit.png");  // �̹��� ������ �ʱ�ȭ
        missileLaunched = false;
        // ���� �� ����ġ�� ó��
       switch (stageNumber) {
       case 1:
           missileDirection = sf::Vector2f(0, 1);
           break;
       case 2:
           missileDirection = sf::Vector2f(-1, 0);
           break;
       case 3:
           missileDirection = sf::Vector2f(-1, 1);
           break;
       default:
           std::cout << "���� ������ ����" << std::endl;
           missileDirection = sf::Vector2f(0, 0);
           break;
       }
    }
   

    // - ����
    // ����
    void special_attack();
    // ������Ʈ
    void updateAttack();
    // �׸���
    void renderAttack(sf::RenderWindow& window);
    
    
    bool missileLaunched;


private:
    std::vector<Missile> missiles;
    sf::Vector2f missileDirection;

};
