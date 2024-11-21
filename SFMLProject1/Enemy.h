#pragma once
#include "Character.h"
#include "EnemyAttack.h"
#include <memory>
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

class Enemy : public Character {
public:
    Enemy(float health, float speed, sf::Vector2f position, int stageNumber);


    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window);



    void image(const std::string& textureFile);

    void updateDirection(int newDirection = 0); // ���� �������� 

    bool isOffScreen() const; // �߾� 900x900 ������ �������� ȭ�� ������ �������� Ȯ��

    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ

protected:
    int stageNumber;  // �������� ��ȣ
    int direction;    // �� �������������� ���Ǵ� ���� (1: ������, -1: ����)

    float targetX = 0.0f; // ��ǥ X ��ǥ
    float targetY = 0.0f; // ��ǥ Y ��ǥ
    float nextTargetY = 0.0f; // �ϴ� ��������: ���� Y ��ǥ��
    float nextTargetX = 1350.0f; // �ٴ� ��������: ���� X ��ǥ��

    std::unique_ptr<EnemyAttack> attackPattern;
};

class NormalUnit : public Enemy {

public:
    NormalUnit(int stageNumber, sf::Vector2f position)
        : Enemy(100.0f, 1.0f, position, stageNumber) {
        image(stageNumber == 1 ? "sky_enemy_unit.png" :
              stageNumber == 2 ? "sea_enemy_unit_b.png" :
                                 "land_enemy_unit.png"); // �̹��� ����
    }



};

class EliteUnit : public Enemy {

public:
    EliteUnit(int stageNumber, sf::Vector2f position)
        : Enemy(300.0f, 1.5f, position, stageNumber) {
        
        missileLaunched = false;
        // ���� �� ����ġ�� ó��
       switch (stageNumber) {
       case 1:
           image("sky_elite_unit.png");  // �̹��� ������ �ʱ�ȭ
           missileDirection = sf::Vector2f(0, 1);
           break;
       case 2:
           image("sea_elite_unit.png");  // �̹��� ������ �ʱ�ȭ
           missileDirection = sf::Vector2f(-1, 0);
           break;
       case 3:
           image("land_elite_unit.png");  // �̹��� ������ �ʱ�ȭ
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
