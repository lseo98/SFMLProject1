#include "Game.h"
#include <iostream>


Game::Game() {
    initVariables();
    initWindow();
}

Game::~Game() {
    window->clear();
    for (auto* enemy : enemies) {
        delete enemy;
    }
    delete window;
}

void Game::initVariables() {
    window = nullptr;   // 윈도우 초기화
    isRunning = true;   
    isMaingameRunning = true;   // stage 1, 2, 3이 아닌 미니게임 혹은 화면 전환 중에는 false
    this->clock.restart(); // 추후 미니게임 혹은 메인 게임 시작 후 시간 계산하는 것으로 변경 필요
    stageNumber = 1;        // 1: 하늘, 2: 바다, 3: 땅
    currentStage.setStage(stageNumber, player, enemies);    // 현재 스테이지 초기화
    spawnEnemies();  // 초기 스테이지의 적 유닛을 생성
}

void Game::initWindow() {
   
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages"); // 윈도우 게임화면 렌더링
    // 전체 화면 (그래픽 볼 때 전체화면으로 미리 실행해보면 좋을 것 같아서 넣음)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);
    
    window->setFramerateLimit(60);  // 프레임 속도 제한, 초당 60프레임
}
// 새로운 spawnEnemies 함수 정의
void Game::spawnEnemies() {
    // 기존 적 유닛 메모리 해제
    for (auto* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    // 스테이지 번호에 따라 적 유닛 생성
    if (stageNumber == 1) {
        enemies.push_back(new NormalUnit(stageNumber));  // 하늘 스테이지의 적
        enemies.push_back(new EliteUnit(stageNumber));
    }
    else if (stageNumber == 2) {
        enemies.push_back(new NormalUnit(stageNumber));  // 바다 스테이지의 적
        enemies.push_back(new EliteUnit(stageNumber));
    }
    else if (stageNumber == 3) {
        enemies.push_back(new NormalUnit(stageNumber));  // 땅 스테이지의 적
        enemies.push_back(new EliteUnit(stageNumber));
        // 땅 스테이지에서 보스 등장 (필요시 Boss 클래스의 생성자도 수정)
        enemies.push_back(new Boss(/* 필요한 인수 */));
    }
}


void Game::run() {
    while (isRunning && window->isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // 프레임 간 경과 시간 측정
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // 창 닫거나 esc 누른 경우 게임 종료
            isRunning = false;
            window->close();
        }
        //  특수 공격 : E 키를 눌렀을 때 수행
        if(event.type == sf::Event::KeyPressed) {   // 한 번 눌렀을 때 한 개만 생성되도록 키를 새로 눌렀을 경우에만 실행
            if (event.key.code == sf::Keyboard::E) {
                player.performSpecialAttack(); // E 키를 눌렀을 때 한 번만 호출
            }
            // 숫자 입력에 따른 맵 전환 // 1: 하늘, 2: 바다, 3: 땅

            if (event.key.code == sf::Keyboard::Num1) {
                stageNumber = 1;
                player.setStage(stageNumber); // Player 클래스에 스테이지 번호 전달
                currentStage.setStage(stageNumber, player, enemies);
                spawnEnemies();
            }
            else if (event.key.code == sf::Keyboard::Num2) {
                stageNumber = 2;
                player.setStage(stageNumber); // Player 클래스에 스테이지 번호 전달
                currentStage.setStage(stageNumber, player, enemies);
                spawnEnemies();
            }
            else if (event.key.code == sf::Keyboard::Num3) {
                stageNumber = 3;
                player.setStage(stageNumber); // Player 클래스에 스테이지 번호 전달
                currentStage.setStage(stageNumber, player, enemies);
                spawnEnemies();
            }

        }   
    }
}

void Game::update() { // 게임 상태 업데이트
    float dt = clock.restart().asSeconds(); // 밀리초 단위로 변환 
 
    float speed = player.get_speed();
    float dx = 0.0f, dy = 0.0f;

    // 플레이어 움직임 업데이트
    dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
    dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;
    
    if (dx * dy) {  // 대각선 이동의 경우 좌우, 상하 단일 움직임 보다 빨라지는 속도를 보정
        dx *= 0.7;
        dy *= 0.7;
    }

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        dy -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        dy += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx += speed;
    }*/

    for (float i = 0; i < 1; i += dt) player.move(sf::Vector2f(dx * dt, dy * dt));
    
}

void Game::render() {
    window->clear(); // 화면 지우기

    currentStage.update(player, enemies, *window);
    // player.draw(playerSpeed * dt, 0);
     // 여기에서 게임 객체를 그리기 (예: player, enemy 등)
    player.draw(*window);
    // 현재 공격 전략을 통해 발사체 업데이트 및 그리기
    if (player.getAttackStrategy()) {
        player.getAttackStrategy()->updateProjectiles(*window);         
    }

    // 적 업데이트 및 화면에 그리기
    for (auto* enemy : enemies) {
        enemy->attack();         // 적의 공격 수행
        enemy->draw(*window);     // 적을 화면에 그리기
    }


    window->display(); // 화면에 그린 내용을 표시
}



