#pragma once
#include "Character.h"
#include "Enemy.h" 
//#include "Boss.h" 
//#include <memory>
#include <iostream>
#include "Projectile.h"
#include "Missile.h"
#include "Bullet.h"
#include <vector>
class Boss;


class Player : public Character {
public:
    Player();
    

    float power = 150.0f;

    void move(sf::Vector2f updatePosition);
   // void takeDamage(float amount) override;
    void draw(sf::RenderWindow& window) override; 
    void updateDirection(char direction,int stageNum); // ���� ���� ����
    void image(std::string textureFile, const sf::IntRect& textureRect);
    void initializeHearts();

    // �������� ��ȯ�� �÷��̾� ����
    void setPlayer(int stageNumber);  

    void restart();
    
    sf::Texture heartTexture; // ��Ʈ �ؽ�ó
    std::vector<sf::Sprite> hearts; // ��Ʈ�� ǥ���� ��������Ʈ �迭
    void changeHeartSprite();

    // - ����
    // ����
    void basicAttack();
    void specialAttack();
    void ultimateAttack();
    // ������Ʈ
    void collision(std::vector<Enemy*>& enemies);    // ����ü-�� �浹 ó��
    void enemyProjectileCollision(std::vector<std::unique_ptr<Missile>>& globalMissiles, std::vector<Enemy*>& enemies); // ����ü-����ü �浹ó��
    void healUnitCollision(std::vector<HealUnit*> healUnits);  // ���� �������� / ����ü-������ �浹ó��// ����ü-�� �浹 ó��
    void shieldCollision(std::vector<Shield*> shield);  // ���� �������� / ����ü-���շ� �浹ó��
    void bossCollision(Boss *boss);                     // ���� �������� / ����-����ü �浹 ó��
    void deleteThisProjectile();                     // �浹�� �� �߻�ü ����
    void updateAttack();                             // ����ü ������Ʈ
    void updateAllies(float delatime, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Missile>>& globalMissiles);
    // �׸���
    void renderAttack(sf::RenderWindow& window);
    void drawAllies(sf::RenderWindow& window);  // �Ʊ� ���� �׸��� �޼��� �߰�
    void allyAttack();

    // ��Ÿ�� ���� ������Ʈ �޼��� �߰�
    void updateCooldowns(float dt);  // ��Ÿ�� ������Ʈ (Ư�����ݰ� �ʻ�� ��� ����)
    
    void countKillNormal() { this->killCountNomalUnit++; }
    void countKillElite();


    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ

    sf::Vector2f bulletStartPosition;

    // �ñر� ���� ��Ÿ�� ��ȯ �Լ�
    float getUltimateAttackRemainingCooldown() const;
    float getUltimateAttackCooldown() { return ultimateAttackCooldown; }
    // Ư�� ���� ���� ��Ÿ�� ��ȯ �Լ�
    float getSpecialAttackRemainingCooldown() const;
    float getSpecialAttackCooldown() { return specialAttackCooldown; }

    sf::Vector2f getPosition() const {
        return position; // �÷��̾��� ���� ��ġ�� ��ȯ
    }
    void takeDamage(float amount) override;

    // ������
    void triggerBlink();             // ������ ����
    void updateBlink();              // ������ ���� ������Ʈ

    // �߻�ü ���� ��ȯ �Լ�
    std::vector<Bullet*>& getBullets() { return bullets; }
    std::vector<Missile*>& getMissiles() { return missiles; }
    std::vector<Missile*>& getAllyMissiles() { return allyMissiles; }

    // óġ�� ���� ��
    int killCountNomalUnit, killCountEliteUnit1, killCountEliteUnit2, killCountEliteUnit3, maxKillEliteCount = 30;

    void setSpecialAttackCooldown(float cooldown) {
        specialAttackCooldown = cooldown;
    }

    enum class ExplosionType {
        EnemyDestroyed,
        MissileImpact,
        Q_missileImpact
    };
    struct Explosion {
        sf::Sprite sprite;
        float elapsedTime;
        float frameTime;
        int currentFrame;
        int totalFrames;
        ExplosionType type; // ���� Ÿ��
    };
    std::vector<Explosion> explosions; // ���� ����Ʈ
    sf::Texture enemyExplosionTextures[4]; // ���������� ���� �ؽ�ó
    sf::Texture missileExplosionTextures[4]; // ���������� ���� �ؽ�ó
    sf::Texture Q_missileExplosionTextures[4]; // ���������� ���� �ؽ�ó


    void loadExplosionTextures(); // ���� �ؽ�ó �ε�
    void createExplosion(sf::Vector2f position, ExplosionType type); // ���� ����

    void updateExplosions(float dt); // ���� �ִϸ��̼� ������Ʈ
    void renderExplosions(sf::RenderWindow& window); // ���� ������
    void clearExplosions(); //���� �����


private:

    std::vector<Bullet*> bullets;
    std::vector<Missile*> missiles;
    std::vector<Missile*> allyMissiles;    // �Ʊ� ���ֵ��� �߻��� �̻��� ���� 

    sf::Vector2f bulletDirection; // �⺻ ���� ����  
    sf::Vector2f missileDirection;
    char direction;

    // Ư�� ���� ��Ÿ�� ���� ����
    float specialAttackCooldown;    // Ư�� ���� ��Ÿ�� (�� ����)
    float timeSinceLastSpecial;     // ������ Ư�� ���� ���� ��� �ð�
    bool canSpecialAttack = true;          // Ư�� ���� ���� ����

    // �ʻ�� ��Ÿ�� ���� ����
    float ultimateAttackCooldown;   // �ʻ�� ��Ÿ�� (�� ����)
    float timeSinceLastUltimate;    // ������ �ʻ�� ���� ��� �ð�
    bool canUltimateAttack = true;         // �ʻ�� ���� ����

    // �ʻ�� �Ʊ� ���� ��� ����
    std::vector<sf::Sprite> allyUnits; // �Ʊ� ���ֵ��� �����ϴ� ��� ����
    sf::Texture allyTexture;           // �Ʊ� ������ �ؽ�ó
    sf::Texture MissileTextures[4];   // ���������� �߻�ü �̹��� (1: �ϴ�, 2: �ٴ�, 3: ��) 
    sf::Texture AllMissileTextures[4];   // ���������� �ʻ�� �̹��� (1: �ϴ�, 2: �ٴ�, 3: ��) 

    float waitTime;  // �ϴ� ������������ �Ʊ� ������ ��� �ð�

    sf::Texture bulletTextures[4];   // ���������� �߻�ü �̹��� (1: �ϴ�, 2: �ٴ�, 3: ��) 
    int stageNumber;                 // ���� �������� ��ȣ
    void loadProjectileTextures();

    // óġ�� ���� ��
    //int killCountNomalUnit, killCountEliteUnit1, killCountEliteUnit2, killCountEliteUnit3;

    // ������
    bool isBlinking = false;         // ������ ����
    sf::Clock blinkClock;            // ������ Ÿ�̸�
    float blinkDuration = 1.0f;      // ������ ���� �ð� (��)
    float blinkInterval = 0.1f;      // �����̴� ���� (0.1�ʸ��� ���)
    bool isVisible = true;           // ���� ���̴� ����

    bool isOnGround = false; // �ٴ� �浹 ���� �÷���
};
