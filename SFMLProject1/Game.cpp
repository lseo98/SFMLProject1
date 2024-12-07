#include "Game.h"
#include <iostream>

// 정적 멤버 정의
sf::Clock Game::globalClock;

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
      //  std::cout << player.getHealth() << std::endl;
        if (player.getHealth() <= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                player.restart();
                boss.initBoss();
                stageSwitchCounter = 1;
                stageNumber = 1;
                for (Enemy* enemy : enemies) {
                    delete enemy;
                }
                enemies.clear();
                /*for (Missile* enemyMissile : enemyMissiles) {
                    delete enemyMissile;
                }*/
                enemyMissiles.clear();
                bossMissiles.clear();
                currentStage.setStage(1, enemies);
            }
        }
        else if (stageNumber != 5) update();

        render();
    }
}


void Game::initVariables() {
    globalClock.restart(); // 게임 시작 시 Clock 초기화

    window = nullptr;   // 윈도우 초기화
    isRunning = true;   
    isMaingameRunning = true;   // stage 1, 2, 3이 아닌 미니게임 혹은 화면 전환 중에는 false
    this->clock.restart(); // 추후 미니게임 혹은 메인 게임 시작 후 시간 계산하는 것으로 변경 필요
    stageNumber = 1;        // 1: 하늘, 2: 바다, 3: 땅

    uiManager.setStageChangeCallback([this](int stage) {
        this->changeStage(stage); // 콜백에서 Game의 메서드를 호출
        });

    EliteUnit::initializeTextures(); // 여기서 호출

    currentStage.setStage(stageNumber, enemies);    // 현재 스테이지 초기화
    currentStage.spawnEnemies(enemies, dt);             // 이전 스테이지 적군 삭제 및 초기화

    player.setPlayer(stageNumber);  // 아군 유닛 초기화

	uiManager.init(); // UI 초기화

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
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // 창 닫거나 esc 누른 경우 게임 종료
            isRunning = false;
            window->close();
        }
        
        // UIManager에 이벤트 전달
        uiManager.handleEvent(event,*window);
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
                    enemyMissiles.clear();
                    currentStage.spawnEnemies(enemies, dt);
                }
                // 다른 곳을 클릭하면 포커스 비활성화
                else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    stageNumber = 2;
                    currentStage.setStage(stageNumber, enemies);
                    player.setPlayer(stageNumber);
                    player.setPosition(sf::Vector2f(WINDOWWIDTH / 4.0f, WINDOWHEIGHT / 2.0f));
                    currentStage.spawnEnemies(enemies, dt);
                    enemyMissiles.clear();
                }
                else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    stageNumber = 3;
                    currentStage.setStage(stageNumber, enemies);
                    player.setPlayer(stageNumber);
                    player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 4.0f * 3.0f + 29.0f));
                    currentStage.spawnEnemies(enemies, dt);
                    enemyMissiles.clear();
                }
                else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                    stageNumber = 4;
                    currentStage.setStage(3, enemies);
                    player.setPlayer(3);
                    player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f - 200, WINDOWHEIGHT / 4.0f * 3.0f + 29.0f));
                    currentStage.spawnEnemies(enemies, dt);
                    enemyMissiles.clear();
                }
                else if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                    stageNumber = 5;
                    enemyMissiles.clear();
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
                    // 보스 패턴 테스트용 // 이거 사용 시 game update에 가서 boss.attack 주석처리해야
                    if (event.key.code == sf::Keyboard::T) {
                        if (stageNumber == 4) boss.attack(dt, player, bossMissiles);
                    }
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
                if (stageNumber == 3 || stageNumber == 4) {
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

void Game::changeStage(int newStageNumber) {
    stageNumber = newStageNumber;          // 스테이지 번호 설정
    currentStage.setStage(stageNumber, enemies); // 현재 스테이지 적 초기화
    player.setPlayer(stageNumber);        // 플레이어 초기화

    // 스테이지별 플레이어 초기 위치 설정
    if (stageNumber == 1) {
        player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 9.0f / 10.0f));
    }
    else if (stageNumber == 2) {
        player.setPosition(sf::Vector2f(WINDOWWIDTH / 4.0f, WINDOWHEIGHT / 2.0f));
    }
    else if (stageNumber == 3) {
        player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 4.0f * 3.0f + 29.0f));
    }
    else if (stageNumber == 4) {
        player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f - 200, WINDOWHEIGHT / 4.0f * 3.0f + 29.0f));
    }

    currentStage.spawnEnemies(enemies, dt); // 적군 생성
    enemyMissiles.clear();                  // 기존 적 미사일 제거
}


void Game::checkStageTransition() {
    // 30초 경과 시 스테이지 이동
    if (globalClock.getElapsedTime().asSeconds() > 30.0f * stageSwitchCounter) {
        // 스테이지 이동
        if (stageSwitchCounter < 3) {
            stageNumber++; // 다음 스테이지로 이동
        }
        else {
            if (stageNumber == 1) {
                stageNumber = (rand() % 2 == 0) ? 2 : 3; // 2 또는 3으로 이동
            }
            else if (stageNumber == 2) {
                stageNumber = (rand() % 2 == 0) ? 1 : 3; // 1 또는 3으로 이동
            }
            else if (stageNumber == 3) {
                stageNumber = (rand() % 2 == 0) ? 1 : 2; // 1 또는 2로 이동
            }
        }

        if (stageNumber == 1) {
            currentStage.setStage(stageNumber, enemies);
            player.setPlayer(stageNumber);
            player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 9.0f / 10.0f));
            enemyMissiles.clear();
            currentStage.spawnEnemies(enemies, dt);
        }
        else if (stageNumber == 2) {
            currentStage.setStage(stageNumber, enemies);
            player.setPlayer(stageNumber);
            player.setPosition(sf::Vector2f(WINDOWWIDTH / 4.0f, WINDOWHEIGHT / 2.0f));
            currentStage.spawnEnemies(enemies, dt);
            enemyMissiles.clear();
        }
        else if (stageNumber == 3) {
            currentStage.setStage(stageNumber, enemies);
            player.setPlayer(stageNumber);
            player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 4.0f * 3.0f + 29.0f));
            currentStage.spawnEnemies(enemies, dt);
            enemyMissiles.clear();
        }
        stageSwitchCounter++;
    }
}


void Game::update() { // 게임 상태 업데이트
    if (player.getHealth() > 0) {
        // 스테이지 자동 전환 검사
        checkStageTransition();

        eliteUnitKillText.setString(killInfo); // 텍스트 설정
        static sf::Clock attackClock; // 자동 발사 간격을 위한 시계
        static sf::Clock allyAttackClock;

        // 플레이어 쿨타임 업데이트
        player.updateCooldowns(dt);
        // 궁극기 쿨타임 정보 얻기
        float remainingUltimateCooldown = player.getUltimateAttackRemainingCooldown();
        float ultimateCooldownRatio = remainingUltimateCooldown / player.getUltimateAttackCooldown();
        // 특수 공격 쿨타임 정보 얻기
        float remainingSpecialCooldown = player.getSpecialAttackRemainingCooldown();
        float specialCooldownRatio = remainingSpecialCooldown / player.getSpecialAttackCooldown();
        uiManager.setCooldownRatios(ultimateCooldownRatio, specialCooldownRatio);
        if (!uiManager.isInputFocused()) {
            float speed = player.getSpeed();
            float dx = 0.0f, dy = 0.0f;

            // 플레이어 움직임 업데이트
            dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
            dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;

            if (stageNumber == 3 || stageNumber == 4) dy = 0; // 스테이지 3에서는 y축 이동 불가
            else if (dx != 0 && dy != 0) { // 대각선 이동 속도 보정
                dx *= 0.7071f;
                dy *= 0.7071f;
            }

            for (float i = 0; i < 1; i += this->dt) player.move(sf::Vector2f(dx * dt, dy * dt));

        }

        // 100ms 간격으로 기본 공격 발사
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
        //else if (stageNumber == 2) {
        //    // 바다 스테이지: 500ms 간격으로 발사
        //    if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
        //        player.allyAttack(); // 아군 유닛 기본 공격 발사
        //        allyAttackClock.restart(); // 타이머 초기화
        //    }
        //}
        else if (stageNumber == 3 || stageNumber == 4) {
            // 땅 스테이지: 500ms 간격으로 발사
            if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
                player.allyAttack(); // 아군 유닛 기본 공격 발사
                allyAttackClock.restart(); // 타이머 초기화
            }
        }

        player.updateAllies(dt, enemies, enemyMissiles);
        // 플레이어 공격 업데이트
        player.collision(enemies);
        player.updateAttack();

        // 플레이어 업데이트
        player.updateBlink(); // 깜빡임 상태 업데이트

        sf::Vector2f playerPosition = player.getPosition(); // 플레이어 위치 가져오기

        // 적 생성 및 업데이트
        currentStage.spawnEnemies(enemies, dt);
        for (auto* enemy : enemies) {
            enemy->collision(player);
            enemy->update(dt);  

            if (EliteUnit* elite = dynamic_cast<EliteUnit*>(enemy)) {
                elite->fireMissile(player.getPosition(), enemyMissiles); // 플레이어를 목표로 미사일 발사
                // 새로 생성된 미사일을 즉시 업데이트
                /*if (!enemyMissiles.empty()) {
                    enemyMissiles.back()->update(); // 방금 추가된 미사일을 바로 업데이트
                }*/
            }
        }

        player.enemyProjectileCollision(enemyMissiles); // 적군 공격체와 플레이어, 플레이어 공격체 간 충돌 처리
        enemyMissiles.erase(                            // 충돌 된 적군 공격체 삭제
            std::remove_if(enemyMissiles.begin(), enemyMissiles.end(),
                [](std::unique_ptr<Missile>& missile) {
                    return missile->checkCrashed();
                }),
            enemyMissiles.end()
        );


        for (auto& enemyMissile : enemyMissiles) { 
            enemyMissile->update(player.getPosition());
        }
        player.updateExplosions(dt);

        //// 화면 밖 미사일 삭제
        //enemyMissiles.erase(
        //    std::remove_if(enemyMissiles.begin(), enemyMissiles.end(),
        //        [](Missile* missile) {
        //            return missile->isOffScreen();
        //        }),
        //    enemyMissiles.end()
        //);

        //sf::Vector2f playerPosition = player.getPosition(); // 플레이어 위치 가져오기

        //// 적 미사일 발사
        //for (auto* enemy : enemies) {
        //    enemy->fireMissile(enemyMissiles, playerPosition); // 플레이어를 목표로 미사일 발사
        //}

        //// 적 미사일 업데이트
        //for (auto* missile : enemyMissiles) {
        //    missile->targeting(playerPosition); // 플레이어를 향해 이동
        //}

        /* if (attackClock.getElapsedTime().asMilliseconds() >= 500) {
             for (auto* enemy : enemies) {
                 enemy->collision(player);
             }
         }*/

         // stage 4 에서 보스 공격 처리
        if (stageNumber == 4) {
            //boss.attack(dt, player, bossMissiles);
            boss.updateAttack(dt, player, bossMissiles);
            
            // 플레이어, 플레이어 미사일과 보스미사일 충돌 처리
            player.enemyProjectileCollision(bossMissiles);
            bossMissiles.erase(                            // 충돌 된 보스 미사일 삭제
                std::remove_if(bossMissiles.begin(), bossMissiles.end(),
                    [](std::unique_ptr<Missile>& missile) {
                        return missile->checkCrashed();
                    }),
                bossMissiles.end()
            );
        }

        // 화면 밖 적 제거
        deleteEnemy();
        uiManager.update(stageNumber, false, player);
    }
    else {
        // 게임 오버 상태 처리
        uiManager.update(stageNumber, true, player);
    }

}

void Game::render() {
    window->clear(); // 화면 지우기

    // (1) 게임 뷰를 설정하고 게임 관련 요소 그리기
    window->setView(gameView); // 게임 뷰 설정 (중앙 정사각형 영역)

    // 배경 그리기
    if (stageNumber != 5) currentStage.drawBackground(*window);
    else {} // 미니게임 배경 삽입 필요


    // 적 관련 그리기

    if (stageNumber != 5){
        for (auto* enemy : enemies) {
            enemy->draw(*window);     // 적을 화면에 그리기
        }

        // 적 미사일 렌더링
        for (auto& missile : enemyMissiles) {
            missile->draw(*window);
        }

        player.renderAttack(*window);

        player.drawAllies(*window);
    }

    if (stageNumber == 4) boss.render(*window,bossMissiles);
    player.renderExplosions(*window);

    window->setView(uiView); // UI 뷰 설정 (전체 화면 영역)

    // UI 그리기
    uiManager.render(*window);
    if (player.getHealth() <= 0) {
        // 게임 오버 화면 그리기
        uiManager.drawGameOverScreen(*window);
    }
    if (stageNumber != 5) player.draw(*window);

    window->display(); // 화면에 그린 내용을 표시
}


void Game::deleteEnemy() {
    
    // 화면 밖으로 나갔거나 채력이 0 이하인 적 제거
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [this](Enemy* enemy) {
                if (enemy->isOffScreen()) {  
                    delete enemy; // 메모리 해제
                    return true; // 제거 대상
                }
                else if(enemy->getHealth() <= 0) {  // 격추 당한 적군 수 
                    if (dynamic_cast<NormalUnit*>(enemy) == enemy) this->player.countKillNormal();
                    else if (dynamic_cast<EliteUnit*>(enemy) == enemy) this->player.countKillElite();
                    delete enemy; // 메모리 해제
                    return true; // 제거 대상
                }
                return false; // 유지 대상
            }),
        enemies.end());
    
    // 화면 밖 미사일 삭제
    enemyMissiles.erase(
        std::remove_if(enemyMissiles.begin(), enemyMissiles.end(),
            [](std::unique_ptr<Missile>& missile) {
                return missile->isOffScreen();
            }),
        enemyMissiles.end()
    );
}