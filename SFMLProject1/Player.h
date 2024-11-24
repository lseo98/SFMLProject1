#pragma once
#include "Character.h"

//#include <memory>
#include <iostream>
#include "Projectile.h"
#include "Missile.h"
#include "Bullet.h"

class Player : public Character {
public:
    Player();
    

    float power = 150.0f;

    void move(sf::Vector2f updatePosition);
    void take_damage(float amount) override;
    void draw(sf::RenderWindow& window) override; 
    void updateDirection(char direction,int stageNum); // ���� ���� ����
    void image(std::string textureFile);
    
    // �������� ��ȯ�� �÷��̾� ����
    void setPlayer(int stageNumber);  
    
   

    // - ����
    // ����
    void basic_attack();
    void special_attack();
    void ultimate_attack();
    // ������Ʈ
    void updateAttack();
    // �׸���
    void renderAttack(sf::RenderWindow& window);
    

    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ

    bool missileLaunched;

private:

    std::vector<Bullet> bullets;
    std::vector<Missile> missiles;
    sf::Vector2f bulletDirection; // �⺻ ���� ����  
    sf::Vector2f missileDirection;
    char direction;
};
