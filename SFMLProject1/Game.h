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
//extern bool isGameOver = false; // 게임 상태를 관리하는 전역 변수

class Game {
public:
    // 생성자 및 소멸자
    Game();
    ~Game();
    static sf::Clock globalClock; // 정적 멤버로 선언
    static sf::Clock stageTransitionClock; // 스테이지 전환을 위한 개별 클럭

    // 게임 실행
    bool run();
   

private:
    // 초기화 함수
    void initWindow();
    void initVariables();

    // 게임 루프의 세 가지 주요 단계( 스테이지 1~4 업데이트 / 스테이지 5 업데이트)
    void handleEvents();
    void update();
    void minigameUpdate();

    void render();

    // 게임 루프 내 필요 함수
    void deleteEnemy();
    void checkStageTransition(); // 스테이지 전환 검사 함수 선언
    void backStageTransition();  // 미니게임에서 스테이지로 복귀
    void changeStage(int newStageNumber); //문자열 입력에 따라 스테이지 변경

    int stageSwitchCounter = 1; // 스테이지 전환 카운터


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
    int minigameOccured;
    int minigameInput[3];  // 미니게임 입력 값 ui 전달 배열   // 0 : 남은 키, 1 : 플레이어 입력 키, 2 : 입력해야할 키
    std::vector<std::unique_ptr<Missile>> enemyMissiles; // 적 미사일을 관리하는 전역 벡터
    std::vector<std::unique_ptr<Missile>> bossMissiles; // 보스 미사일


    // 초기 객체 생성
    Player player;
    std::vector<Enemy*> enemies;
    Boss *boss;
    Stage currentStage;
    Minigame* minigame;
    int stageNumber;        // 1: 하늘, 2: 바다, 3: 땅
    int lastStageNumber;

    UIManager uiManager; // UIManager 객체 추가
    // 엘리트 유닛 관련 변수들
    std::map<int, int> eliteUnitKillCounts; // 스테이지별 엘리트 유닛 사망 횟수
    std::string killInfo;                   // 엘리트 유닛 킬 정보 문자열

    // 폰트 및 텍스트 관련 변수들
    sf::Font font;                // 폰트 객체
    sf::Text eliteUnitKillText;   // 엘리트 유닛 킬 정보를 표시할 텍스트

    bool hasBossStageTransitioned = false; // 이미 보스 스테이지로 강제 이동했는지 여부

};
