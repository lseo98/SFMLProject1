#include "Game.h"
#include <iostream>

Game::Game() {
    initVariables();
    initWindow();
}

Game::~Game() {
    //window->draw(gameover);
    //window->display();

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
        }
        else update();
   
        render();
    }
}

//void Game::run() {
//    while (isRunning && window->isOpen() && player.getHealth()) {
//        sf::Event event;
//        //sf::Time deltaTime = clock.restart(); // 프레임 간 경과 시간 측정
//        dt = clock.restart().asSeconds(); // 프레임 간 경과 시간 측정
//        handleEvents();
//        update();
//        render();
//    }
//}

void Game::initVariables() {
    window = nullptr;   // 윈도우 초기화
    isRunning = true;   
    isMaingameRunning = true;   // stage 1, 2, 3이 아닌 미니게임 혹은 화면 전환 중에는 false
    this->clock.restart(); // 추후 미니게임 혹은 메인 게임 시작 후 시간 계산하는 것으로 변경 필요
    stageNumber = 1;        // 1: 하늘, 2: 바다, 3: 땅

    currentStage.setStage(stageNumber, enemies);    // 현재 스테이지 초기화
    currentStage.spawnEnemies(enemies, dt);             // 이전 스테이지 적군 삭제 및 초기화

    player.setPlayer(stageNumber);  // 아군 유닛 초기화


    currentStage.setStage(stageNumber, enemies);    // 현재 스테이지 초기화

    // 엘리트 유닛 사망 텍스트 초기화
    eliteUnitKillText.setFont(font);
    eliteUnitKillText.setCharacterSize(24);
    eliteUnitKillText.setFillColor(sf::Color::White);
    eliteUnitKillText.setPosition(1375, 500); // 화면 우측 위치
    eliteUnitKillText.setString("0"); // 초기값

    // 폰트 로드
    if (!font.loadFromFile("R2.ttc")) {
        std::cerr << "폰트 파일을 로드할 수 없습니다." << std::endl;
    }

    // 게임 오버 텍스트 설정
    gameover.setFont(font);
    gameover.setString("GAME OVER");
    gameover.setFillColor(sf::Color::Black);

    gameover.setCharacterSize(80);
    gameover.setFillColor(sf::Color::White);

    // 텍스트를 화면 중앙에 위치시키기 위해 중심점을 설정
    sf::FloatRect textRect = gameover.getLocalBounds();
    gameover.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    gameover.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f));


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

    // 왼쪽 입력 상자 설정
    inputBoxl.setSize(sf::Vector2f(450, 900));
    inputBoxl.setPosition(0, 0);
    inputBoxl.setFillColor(sf::Color::Black);
    inputBoxl.setOutlineColor(sf::Color::Green);
    inputBoxl.setOutlineThickness(2);

    // 오른쪽 입력 상자 설정
    inputBoxr.setSize(sf::Vector2f(450, 900));
    inputBoxr.setPosition(1350, 0);
    inputBoxr.setFillColor(sf::Color::Black);
    inputBoxr.setOutlineColor(sf::Color::Green);
    inputBoxr.setOutlineThickness(2);

    // 오른쪽 작은 상자 설정
    smallBoxr.setSize(sf::Vector2f(400, 300));
    smallBoxr.setPosition(1375, 200);
    smallBoxr.setFillColor(sf::Color::Black);
    smallBoxr.setOutlineColor(sf::Color::White);
    smallBoxr.setOutlineThickness(5);

    textbox.setFont(font);
    textbox.setString("Welcome to the\n<Biocommander-II> terminal.\n\n___________________________\n\n>System\n\nFrendly unit destroyed.\n\n>System\n\n*Warning\n\nMental power exhausted.\nThe interrogation begins.\n\n>System\nCommand request received.\n\nFrom frendly Navy.\nType switch to help.");
    textbox.setCharacterSize(25);
    textbox.setFillColor(sf::Color::Yellow);
    textbox.setPosition(5, 5);
}




void Game::handleEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // 창 닫거나 esc 누른 경우 게임 종료
            isRunning = false;
            window->close();
        }
        
  
      
        // 숫자 입력에 따른 맵 전환 // 1: 하늘, 2: 바다, 3: 땅
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
            stageNumber = 1;
        }
        // 마우스 버튼 클릭 이벤트 처리
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (inputBoxl.getGlobalBounds().contains(mousePos) ||
                    inputBoxr.getGlobalBounds().contains(mousePos)) {
                    printf("in\n");
                    // 입력 상자를 클릭하면 포커스 활성화
                    isInputActive = true;
                    //  inputBox.setFillColor(sf::Color::Yellow); // 포커스 시 색상 변경 (선택 사항)
                }
                // 다른 곳을 클릭하면 포커스 비활성화
                else {
                    printf("out\n");
                    isInputActive = false;
                }
            }
        }
        // 키보드 입력 처리
        if (isInputActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') {

                // 백스페이스 처리
                if (!userInput.empty()) {
                    userInput.pop_back();
                }
            }
            else if (event.text.unicode == '\r') {
                // 엔터 처리 (필요시 구현)
                userInput += "\n";

            }
            else if (event.text.unicode < 128) {
                // 일반 문자 입력
                userInput += static_cast<char>(event.text.unicode);

            }
            //printf("dlskjf");
            inputText.setString(userInput);
        }
        //게임 내부 클릭시에만 플레이어 특수 공격 및 스테이지 전환 가능
        if (!isInputActive) {

            // 숫자 입력에 따른 맵 전환 // 1: 하늘, 2: 바다, 3: 땅
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                stageNumber = 1;

                currentStage.setStage(stageNumber, enemies);
                player.setPlayer(stageNumber);
                player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 9.0f / 10.0f));
                currentStage.spawnEnemies(enemies, dt);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
                stageNumber = 2;

                currentStage.setStage(stageNumber, enemies);
                player.setPlayer(stageNumber);
                player.setPosition(sf::Vector2f(WINDOWWIDTH / 4.0f, WINDOWHEIGHT / 2.0f));
                currentStage.spawnEnemies(enemies, dt);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
                stageNumber = 3;

                currentStage.setStage(stageNumber, enemies);
                player.setPlayer(stageNumber);
                player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 4.0f * 3));
                currentStage.spawnEnemies(enemies, dt);

                currentStage.setStage(stageNumber, enemies);

            }


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

void Game::update() { // 게임 상태 업데이트
    if (player.getHealth() > 0) {

   
        // 입력 텍스트 설정
        inputText.setFont(font);
        inputText.setString(userInput);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::Yellow); 
        inputText.setPosition(5, 630);

        text.setFont(font);
        text.setString("Remaining Enimies");
        text.setCharacterSize(38);
        text.setFillColor(sf::Color::White);
        text.setPosition(1410, 210);

        skytext.setFont(font);
        skytext.setString("AIR FORCE");
        skytext.setCharacterSize(38);
        skytext.setFillColor(sf::Color(100, 100, 100, 250));
        if (stageNumber == 1)skytext.setFillColor(sf::Color::White);
        skytext.setPosition(1410, 290);

        seatext.setFont(font);
        seatext.setString("NAVY");
        seatext.setCharacterSize(38);
        seatext.setFillColor(sf::Color(100, 100, 100, 250));
        if (stageNumber == 2)seatext.setFillColor(sf::Color::White);
        seatext.setPosition(1410, 340);

        landtext.setFont(font);
        landtext.setString("ARMY");
        landtext.setCharacterSize(38);
        landtext.setFillColor(sf::Color(100, 100, 100, 250));
        if (stageNumber == 3)landtext.setFillColor(sf::Color::White);
        landtext.setPosition(1410, 390);

        for (int stage = 1; stage <= 3; ++stage) { // 스테이지 1, 2, 3 순회
            killInfo += std::to_string(eliteUnitKillCounts[stage]) + "\n";
        }
        eliteUnitKillText.setFont(font);
        eliteUnitKillText.setCharacterSize(38);
        eliteUnitKillText.setFillColor(sf::Color(100, 100, 100, 250));
        eliteUnitKillText.setPosition(1600, 290);

        static sf::Clock attackClock; // 자동 발사 간격을 위한 시계
        static sf::Clock allyAttackClock;

        // 플레이어 쿨타임 업데이트
        player.updateCooldowns(dt); // 쿨타임 업데이트 추가
        if (!isInputActive) {
            float speed = player.getSpeed();
            float dx = 0.0f, dy = 0.0f;

            // 플레이어 움직임 업데이트
            dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
            dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;

            if (stageNumber == 3) dy = 0;
            else if (dx * dy) {  // 대각선 이동의 경우 좌우, 상하 단일 움직임 보다 빨라지는 속도를 보정
                dx *= 0.7;
                dy *= 0.7;
            }

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
        //else if (stageNumber == 2) {
        //    // 바다 스테이지: 500ms 간격으로 발사
        //    if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
        //        player.allyAttack(); // 아군 유닛 기본 공격 발사
        //        allyAttackClock.restart(); // 타이머 초기화
        //    }
        //}
        else if (stageNumber == 3) {
            // 땅 스테이지: 500ms 간격으로 발사
            if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
                player.allyAttack(); // 아군 유닛 기본 공격 발사
                allyAttackClock.restart(); // 타이머 초기화
            }
        }

        player.updateAllies(dt);
        // 플레이어 공격 업데이트
        player.collision(enemies);
        player.updateAttack(enemies);



        // 적 생성 및 업데이트
        currentStage.spawnEnemies(enemies, dt);
        for (auto* enemy : enemies) {
            enemy->collision(player);
            enemy->update(dt);  // 적 상태 업데이트 (필요 시)
            // 적의 공격 수행 (공격 타입에 따라)
        }
        /* if (attackClock.getElapsedTime().asMilliseconds() >= 500) {
             for (auto* enemy : enemies) {
                 enemy->collision(player);
             }
         }*/

        // 화면 밖 적 제거
        deleteEnemy();
    }

}

void Game::render() {
    window->clear(); // 화면 지우기

        // (1) 게임 뷰를 설정하고 게임 관련 요소 그리기
        window->setView(gameView); // 게임 뷰 설정 (중앙 정사각형 영역)

        // 배경 그리기
        currentStage.drawBackground(*window);



        // 적 관련 그리기
        for (auto* enemy : enemies) {
            enemy->draw(*window);     // 적을 화면에 그리기
        }

        window->draw(eliteUnitKillText);


        player.renderAttack(*window);
        player.drawAllies(*window);  // 아군 유닛 그리기 추가


        // (2) UI 뷰를 설정하고 UI 관련 요소 그리기
        window->setView(uiView); // UI 뷰 설정 (전체 화면 영역)


        //입력상좌가 텍스트 그리기
        window->draw(inputBoxl);
        window->draw(inputBoxr);
        window->draw(smallBoxr);

        window->draw(inputText);
        window->draw(text);
        window->draw(skytext);
        window->draw(seatext);
        window->draw(landtext);
        window->draw(textbox);


        // 플레이어 관련 그리기
        player.draw(*window);
        if (player.getHealth() <= 0)
            window->draw(gameover);
    

    window->display(); // 화면에 그린 내용을 표시
}


void Game::deleteEnemy() {
    // 화면 밖으로 나갔거나 채력이 0 이하인 적 제거
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy* enemy) {
                if (enemy->isOffScreen() || enemy->getHealth() <= 0) {  
                    delete enemy; // 메모리 해제
                    return true; // 제거 대상
                }
                return false; // 유지 대상
            }),
        enemies.end());
}