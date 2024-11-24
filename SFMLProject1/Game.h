#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include <string>


extern int WINDOWWIDTH, WINDOWHEIGHT;

class Game {
public:
    // 생성자 및 소멸자
    Game();
    ~Game();

    // 게임 실행
    void run();

private:
    // 초기화 함수
    void initWindow();
    void initVariables();

    // 게임 루프의 세 가지 주요 단계
    void handleEvents();
    void update();
    void render();


    // SFML 멤버 변수
    sf::RenderWindow* window;
    sf::Event event;
    sf::Clock clock;

    // 게임 변수
    bool isRunning;
    bool isMaingameRunning;
    float playerSpeed;  // 예시로 플레이어 이동 속도 변수
    sf::Vector2f bulletDirection;
    sf::Vector2f missileDirection;
    float dt;


    // 초기 객체 생성
    Player player;
    std::vector<Enemy*> enemies;
    Stage currentStage;
    int stageNumber;        // 1: 하늘, 2: 바다, 3: 땅

    // 입력 상자 관련 변수
    sf::RectangleShape inputBoxl;
    sf::RectangleShape inputBoxr;
    sf::RectangleShape smallBoxr;

    bool isInputActive;

    // 텍스트 관련 변수
    sf::Text inputText;
    sf::Text text;
    sf::Font font;
    std::string userInput;
    sf::Text skytext;
    sf::Text seatext;
    sf::Text landtext;
    int ty = 0, tx = 0;

};
