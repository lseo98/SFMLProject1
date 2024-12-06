#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "UIManager.h" 


extern int WINDOWWIDTH, WINDOWHEIGHT;

class Game {
public:
    // ������ �� �Ҹ���
    Game();
    ~Game();
    static sf::Clock globalClock; // ���� ����� ����

    // ���� ����
    void run();
   

private:
    // �ʱ�ȭ �Լ�
    void initWindow();
    void initVariables();

    // ���� ������ �� ���� �ֿ� �ܰ�
    void handleEvents();
    void update();
    void render();

    // ���� ���� �� �ʿ� �Լ�
    void deleteEnemy();


    // SFML ��� ����
    sf::RenderWindow* window;
    sf::Event event;
    sf::Clock clock;

    // ���Ӱ� UI �� 
    sf::View gameView;
    sf::View uiView;

    // ���� ����
    bool isRunning;
    bool isMaingameRunning;
    float playerSpeed;  // ���÷� �÷��̾� �̵� �ӵ� ����
    sf::Vector2f bulletDirection;
    sf::Vector2f missileDirection;
    float dt;

    std::vector<std::unique_ptr<Missile>> enemyMissiles; // �� �̻����� �����ϴ� ���� ����


    // �ʱ� ��ü ����
    Player player;
    std::vector<Enemy*> enemies;
    Boss boss;
    Stage currentStage;
    int stageNumber;        // 1: �ϴ�, 2: �ٴ�, 3: ��

    UIManager uiManager; // UIManager ��ü �߰�
    // ����Ʈ ���� ���� ������
    std::map<int, int> eliteUnitKillCounts; // ���������� ����Ʈ ���� ��� Ƚ��
    std::string killInfo;                   // ����Ʈ ���� ų ���� ���ڿ�

    // ��Ʈ �� �ؽ�Ʈ ���� ������
    sf::Font font;                // ��Ʈ ��ü
    sf::Text eliteUnitKillText;   // ����Ʈ ���� ų ������ ǥ���� �ؽ�Ʈ



};
