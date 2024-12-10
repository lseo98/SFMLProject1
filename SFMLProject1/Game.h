#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "UIManager.h" 
#include "Minigame.h" 


extern int WINDOWWIDTH, WINDOWHEIGHT;
//extern bool isGameOver = false; // ���� ���¸� �����ϴ� ���� ����

class Game {
public:
    // ������ �� �Ҹ���
    Game();
    ~Game();
    static sf::Clock globalClock; // ���� ����� ����
    static sf::Clock stageTransitionClock; // �������� ��ȯ�� ���� ���� Ŭ��

    // ���� ����
    bool run();
   

private:
    // �ʱ�ȭ �Լ�
    void initWindow();
    void initVariables();

    // ���� ������ �� ���� �ֿ� �ܰ�( �������� 1~4 ������Ʈ / �������� 5 ������Ʈ)
    void handleEvents();
    void update();
    void minigameUpdate();

    void render();

    // ���� ���� �� �ʿ� �Լ�
    void deleteEnemy();
    void checkStageTransition(); // �������� ��ȯ �˻� �Լ� ����
    void backStageTransition();  // �̴ϰ��ӿ��� ���������� ����
    void changeStage(int newStageNumber); //���ڿ� �Է¿� ���� �������� ����

    int stageSwitchCounter = 1; // �������� ��ȯ ī����


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
    int minigameOccured;
    int minigameInput[3];  // �̴ϰ��� �Է� �� ui ���� �迭   // 0 : ���� Ű, 1 : �÷��̾� �Է� Ű, 2 : �Է��ؾ��� Ű
    std::vector<std::unique_ptr<Missile>> enemyMissiles; // �� �̻����� �����ϴ� ���� ����
    std::vector<std::unique_ptr<Missile>> bossMissiles; // ���� �̻���


    // �ʱ� ��ü ����
    Player player;
    std::vector<Enemy*> enemies;
    Boss *boss;
    Stage currentStage;
    Minigame* minigame;
    int stageNumber;        // 1: �ϴ�, 2: �ٴ�, 3: ��
    int lastStageNumber;

    UIManager uiManager; // UIManager ��ü �߰�
    // ����Ʈ ���� ���� ������
    std::map<int, int> eliteUnitKillCounts; // ���������� ����Ʈ ���� ��� Ƚ��
    std::string killInfo;                   // ����Ʈ ���� ų ���� ���ڿ�

    // ��Ʈ �� �ؽ�Ʈ ���� ������
    sf::Font font;                // ��Ʈ ��ü
    sf::Text eliteUnitKillText;   // ����Ʈ ���� ų ������ ǥ���� �ؽ�Ʈ

    bool hasBossStageTransitioned = false; // �̹� ���� ���������� ���� �̵��ߴ��� ����

};
