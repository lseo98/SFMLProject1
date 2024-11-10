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
    currentStage.spawnEnemies(enemies);                     // 이전 스테이지 적군 삭제 및 초기화
}

void Game::initWindow() {
   
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages"); // 윈도우 게임화면 렌더링
    // 전체 화면 (그래픽 볼 때 전체화면으로 미리 실행해보면 좋을 것 같아서 넣음)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);
    
    window->setFramerateLimit(60);  // 프레임 속도 제한, 초당 60프레임
}

void Game::run() {
    while (isRunning && window->isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // 프레임 간 경과 시간 측정
        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            isRunning = false;
            window->close();
        }
      //  특수 공격 : E 키를 눌렀을 때 수행
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            player.performSpecialAttack(); // 특수 공격 메서드 호출
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
            stageNumber = 1;
            currentStage.setStage(stageNumber, player, enemies);
            currentStage.spawnEnemies(enemies);
        }
        // else if 의 경우 동시 입력이 처리 안 됨. 따라서 스테이지 전환 요구에서는 적절
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
            stageNumber = 2;
            currentStage.setStage(stageNumber, player, enemies);
            currentStage.spawnEnemies(enemies);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
            stageNumber = 3;
            currentStage.setStage(stageNumber, player, enemies);
            currentStage.spawnEnemies(enemies);
        }

    
    }
}

void Game::update(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds(); // 밀리초 단위로 변환 
    // 게임 상태 업데이트 (예: 플레이어 이동)
    // float dt = deltaTime.asSeconds();
    float speed = player.get_speed();
    float dx = 0.0f, dy = 0.0f;
   
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