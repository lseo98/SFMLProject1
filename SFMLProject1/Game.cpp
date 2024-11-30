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

void Game::run() {
    while (isRunning && window->isOpen()) {
        sf::Event event;
        dt = clock.restart().asSeconds(); // 프레임 간 경과 시간 측정
        handleEvents();
        //sf::Time deltaTime = clock.restart(); // 프레임 간 경과 시간 측정  
        if (player.getHealth() <= 0) {
        }
        else update();
   
        render();
    }
}

void Game::initVariables() {
    window = nullptr;   // 윈도우 초기화
    isRunning = true;   
    isMaingameRunning = true;   // stage 1, 2, 3이 아닌 미니게임 혹은 화면 전환 중에는 false
    this->clock.restart(); // 추후 미니게임 혹은 메인 게임 시작 후 시간 계산하는 것으로 변경 필요
    stageNumber = 1;        // 1: 하늘, 2: 바다, 3: 땅

    currentStage.setStage(stageNumber, enemies);    // 현재 스테이지 초기화
    currentStage.spawnEnemies(enemies, dt);             // 이전 스테이지 적군 삭제 및 초기화

    player.setPlayer(stageNumber);  // 아군 유닛 초기화

    uiManager.init();
}

void Game::initWindow() {
   
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages"); // 윈도우 게임화면 렌더링
    // 전체 화면 (그래픽 볼 때 전체화면으로 미리 실행해보면 좋을 것 같아서 넣음)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);
    
    window->setFramerateLimit(60);  // 프레임 속도 제한, 초당 60프레임

    // 중앙 정사각형 영역을 위한 게임 뷰 초기화
    gameView.setCenter(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f); // 화면의 중앙 설정
    gameView.setSize(900, 900); // 전체 화면 크기를 사용해 정사각형 부분만을 볼 수 있게 설정

    // Viewport 설정으로 중앙 900x900 영역만 차지하도록 설정 (창 크기 비율 맞추기)
    float viewportX = (WINDOWWIDTH - 900) / (2.0f * WINDOWWIDTH); // 좌우 여백 비율
    float viewportY = 0.f; // 상하 여백 없음
    float viewportWidth = 900.0f / WINDOWWIDTH; // 중앙 영역 너비 비율
    float viewportHeight = 1.0f; // 전체 높이 사용

    // Viewport 설정
    gameView.setViewport(sf::FloatRect(viewportX, viewportY, viewportWidth, viewportHeight));

    // 전체 화면을 위한 UI 뷰 초기화
    uiView = window->getDefaultView(); // 기본 화면 전체 뷰
}

void Game::handleEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            isRunning = false;
            window->close();
        }
        // UIManager에 이벤트 전달
        uiManager.handleEvent(event);

        // UI에 포커스가 있을 때는 게임 입력을 처리하지 않음
        if (!uiManager.isInputFocused()) {
            // 게임 입력 처리 (스테이지 전환 등)
            if (event.type == sf::Event::KeyPressed) {
                // 스테이지 전환
                if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                    stageNumber = 1;
                    currentStage.setStage(stageNumber, enemies);
                    player.setPlayer(stageNumber);
                    player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 9.0f / 10.0f));
                    currentStage.spawnEnemies(enemies, dt);
                }
                else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    stageNumber = 2;
                    currentStage.setStage(stageNumber, enemies);
                    player.setPlayer(stageNumber);
                    player.setPosition(sf::Vector2f(WINDOWWIDTH / 4.0f, WINDOWHEIGHT / 2.0f));
                    currentStage.spawnEnemies(enemies, dt);
                }
                else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    stageNumber = 3;
                    currentStage.setStage(stageNumber, enemies);
                    player.setPlayer(stageNumber);
                    player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 4.0f * 3));
                    currentStage.spawnEnemies(enemies, dt);
                }

                // 특수 공격 및 방향 전환
                // ...
                if (event.type == sf::Event::KeyPressed) {   // 한 번 눌렀을 때 한 개만 생성되도록 키를 새로 눌렀을 경우에만 실행
                    //  특수 공격 : E 키를 눌렀을 때 수행
                    if (event.key.code == sf::Keyboard::E) {
                        player.specialAttack(); // E 키를 눌렀을 때 한 번만 호출
                    }
                    // 필살기 : Q 키를 눌렀을 때 수행
                    if (event.key.code == sf::Keyboard::Q) {
                        player.ultimateAttack(); // Q 키를 눌렀을 때 한 번만 호출
                    }
                    // 플레이어 좌우 반전
                    if (stageNumber == 2) {
                        if (event.key.code == sf::Keyboard::A) {
                            player.updateDirection('A', 2);
                        }
                        if (event.key.code == sf::Keyboard::D) {
                            player.updateDirection('D', 2);
                        }
                    }
                    if (stageNumber == 3) {
                        if (event.key.code == sf::Keyboard::A) {
                            player.updateDirection('A', 3);
                        }
                        if (event.key.code == sf::Keyboard::D) {
                            player.updateDirection('D', 3);
                        }
                    }
                }
            }
        }
    }
}


void Game::update() { // 게임 상태 업데이트
    if (player.getHealth() > 0) {
        // 엘리트 유닛 킬 정보 업데이트
        killInfo = ""; // 문자열 초기화
        for (int stage = 1; stage <= 3; ++stage) {
            killInfo += std::to_string(eliteUnitKillCounts[stage]) + "\n";
        }
        eliteUnitKillText.setFont(font);
        eliteUnitKillText.setCharacterSize(38);
        eliteUnitKillText.setFillColor(sf::Color(100, 100, 100, 250));
        eliteUnitKillText.setPosition(1600, 290);
        eliteUnitKillText.setString(killInfo); // 텍스트 설정

        static sf::Clock attackClock; // 자동 발사 간격을 위한 시계
        static sf::Clock allyAttackClock;

        // 플레이어 쿨타임 업데이트
        player.updateCooldowns(dt);

        if (!uiManager.isInputFocused()) {
            float speed = player.getSpeed();
            float dx = 0.0f, dy = 0.0f;

            // 플레이어 움직임 업데이트
            dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
            dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;

            if (stageNumber == 3) dy = 0; // 스테이지 3에서는 y축 이동 불가
            else if (dx != 0 && dy != 0) { // 대각선 이동 속도 보정
                dx *= 0.7071f;
                dy *= 0.7071f;
            }

            // 플레이어 이동 적용
            for (float i = 0; i < 1; i += this->dt) player.move(sf::Vector2f(dx * dt, dy * dt));

        }

        // 200ms 간격으로 기본 공격 발사
        if (attackClock.getElapsedTime().asMilliseconds() >= 100) {
            player.basicAttack(); // 기본 공격 발사
            attackClock.restart(); // 타이머 초기화
        }

        // 스테이지에 따른 아군 유닛 발사 속도 조절
        if (stageNumber == 1) {
            // 하늘 스테이지: 100ms 간격으로 발사
            if (allyAttackClock.getElapsedTime().asMilliseconds() >= 100) {
                player.allyAttack(); // 아군 유닛 기본 공격 발사
                allyAttackClock.restart(); // 타이머 초기화
            }
        }
        else if (stageNumber == 3) {
            // 땅 스테이지: 500ms 간격으로 발사
            if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
                player.allyAttack(); // 아군 유닛 기본 공격 발사
                allyAttackClock.restart(); // 타이머 초기화
            }
        }

        // 아군 유닛 업데이트
        player.updateAllies(dt);

        // 플레이어 공격 업데이트
        player.collision(enemies);
        player.updateAttack();

        // 적 생성 및 업데이트
        currentStage.spawnEnemies(enemies, dt);
        for (auto* enemy : enemies) {
            enemy->collision(player);
            enemy->update(dt);  // 적 상태 업데이트
            // 적의 공격 수행 (구현 필요)
        }

        // 화면 밖 적 제거
        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                [](Enemy* enemy) {
                    if (enemy->isOffScreen()) {
                        delete enemy; // 메모리 해제
                        return true; // 제거 대상
                    }
        return false; // 유지 대상
                }),
            enemies.end());

        // UI 업데이트 (게임 진행 중)
       uiManager.update(stageNumber, false);
    }
    else {
        // 게임 오버 상태 처리
        uiManager.update(stageNumber, true);
    }
}

void Game::render() {
    window->clear(); // 화면 지우기

    window->setView(gameView); // 게임 뷰 설정 (중앙 정사각형 영역)

        // 배경 그리기
    currentStage.drawBackground(*window);

    // 게임 오브젝트 그리기
    for (auto* enemy : enemies) {
        enemy->draw(*window);
    }

    player.renderAttack(*window);
    player.drawAllies(*window);
    window->setView(uiView); // UI 뷰 설정 (전체 화면 영역)

    // UI 그리기
    uiManager.render(*window);

    if (player.getHealth() <= 0) {
        // 게임 오버 화면 그리기
        uiManager.drawGameOverScreen(*window);
    }
    player.draw(*window);


    window->display(); // 화면에 그린 내용을 표시
}
