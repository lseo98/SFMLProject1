#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;

class Game {
public:
    // ������ �� �Ҹ���
    Game();
    ~Game();

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


    // SFML ��� ����
    sf::RenderWindow* window;
    sf::Event event;
    sf::Clock clock;

    // ���� ����
    bool isRunning;
    bool isMaingameRunning;
    float playerSpeed;  // ���÷� �÷��̾� �̵� �ӵ� ����
    sf::Vector2f bulletDirection;
    sf::Vector2f missileDirection;



    // �ʱ� ��ü ����
    Player player;
    std::vector<Enemy*> enemies;
    Stage currentStage;
    int stageNumber;        // 1: �ϴ�, 2: �ٴ�, 3: ��
};
