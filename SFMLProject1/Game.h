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
    // 생성자 및 소멸자
    Game();
    ~Game();
    static sf::Clock globalClock; // 정적 멤버로 선언

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

    // 게임 루프 내 필요 함수
    void deleteEnemy();


    // SFML 멤버 변수
    sf::RenderWindow* window;
    sf::Event event;
    sf::Clock clock;

    // 게임과 UI 뷰 
    sf::View gameView;
    sf::View uiView;

    // 게임 변수
    bool isRunning;
    bool isMaingameRunning;
    float playerSpeed;  // 예시로 플레이어 이동 속도 변수
    sf::Vector2f bulletDirection;
    sf::Vector2f missileDirection;
    float dt;

    std::vector<std::unique_ptr<Missile>> enemyMissiles; // 적 미사일을 관리하는 전역 벡터


    // 초기 객체 생성
    Player player;
    std::vector<Enemy*> enemies;
    Boss boss;
    Stage currentStage;
    int stageNumber;        // 1: 하늘, 2: 바다, 3: 땅

    UIManager uiManager; // UIManager 객체 추가
    // 엘리트 유닛 관련 변수들
    std::map<int, int> eliteUnitKillCounts; // 스테이지별 엘리트 유닛 사망 횟수
    std::string killInfo;                   // 엘리트 유닛 킬 정보 문자열

    // 폰트 및 텍스트 관련 변수들
    sf::Font font;                // 폰트 객체
    sf::Text eliteUnitKillText;   // 엘리트 유닛 킬 정보를 표시할 텍스트



};
