#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include <map>

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

    std::vector<Missile*> enemyMissiles; // �� �̻����� �����ϴ� ���� ����


    // �ʱ� ��ü ����
    Player player;
    std::vector<Enemy*> enemies;
    Stage currentStage;
    int stageNumber;        // 1: �ϴ�, 2: �ٴ�, 3: ��


    // �Է� ���� ���� ����
    sf::RectangleShape inputBoxl;
    sf::RectangleShape inputBoxr;
    sf::RectangleShape smallBoxr;

    bool isInputActive;

    // �ؽ�Ʈ ���� ����
    sf::Text gameover;
    sf::Text inputText;
    sf::Text text;
    sf::Font font;
    std::string userInput;
    sf::Text skytext;
    sf::Text seatext;
    sf::Text landtext;
    sf::Text textbox;

    int ty = 0, tx = 0;


    sf::Texture texture;      // �̹��� �ؽ�ó
    sf::Sprite sprite;        // �ؽ�ó�� ����� ��������Ʈ

    sf::Text eliteUnitKillText; // ����Ʈ ���� ��� Ƚ���� ǥ���ϴ� �ؽ�Ʈ
    std::map<int, int> eliteUnitKillCounts; // ���������� ����Ʈ ���� ��� Ƚ��
    std::string killInfo;



};
