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
    
    // �������� ��ȯ�� �÷��̾� ����
    void setPlayer(std::string textureFile, sf::Vector2f bulletDirection, sf::Vector2f missileDirection);  // void image(std::string);


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
    void updateDirection(char direction,int stageNum); // ���� ���� ����

private:

    char direction;
};
