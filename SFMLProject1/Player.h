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
    void basicAttack();
    void specialAttack();
    void ultimateAttack();
    // ������Ʈ
    void updateAttack();
    void updateAllies(float delatime);
    // �׸���
    void renderAttack(sf::RenderWindow& window);
    void drawAllies(sf::RenderWindow& window);  // �Ʊ� ���� �׸��� �޼��� �߰�
    void allyAttack();

    // ��Ÿ�� ���� ������Ʈ �޼��� �߰�
    void updateCooldowns(float dt);  // ��Ÿ�� ������Ʈ (Ư�����ݰ� �ʻ�� ��� ����)
    

    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ

    //bool missileLaunched;

private:

    std::vector<Bullet> bullets;
    std::vector<Missile> missiles;
    std::vector<Missile> allyMissiles;    // �Ʊ� ���ֵ��� �߻��� �̻��� ����

    sf::Vector2f bulletDirection; // �⺻ ���� ����  
    sf::Vector2f missileDirection;
    char direction;

    // Ư�� ���� ��Ÿ�� ���� ����
    float specialAttackCooldown;    // Ư�� ���� ��Ÿ�� (�� ����)
    float timeSinceLastSpecial;     // ������ Ư�� ���� ���� ��� �ð�
    bool canSpecialAttack;          // Ư�� ���� ���� ����

    // �ʻ�� ��Ÿ�� ���� ����
    float ultimateAttackCooldown;   // �ʻ�� ��Ÿ�� (�� ����)
    float timeSinceLastUltimate;    // ������ �ʻ�� ���� ��� �ð�
    bool canUltimateAttack;         // �ʻ�� ���� ����

    // �ʻ�� �Ʊ� ���� ��� ����
    std::vector<sf::Sprite> allyUnits; // �Ʊ� ���ֵ��� �����ϴ� ��� ����
    sf::Texture allyTexture;           // �Ʊ� ������ �ؽ�ó

    float waitTime;  // �ϴ� ������������ �Ʊ� ������ ��� �ð�
};
