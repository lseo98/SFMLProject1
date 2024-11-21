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
        sf::Time deltaTime = clock.restart(); // 프레임 간 경과 시간 측정
        handleEvents();
        update();
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
    currentStage.spawnEnemies(enemies);             // 이전 스테이지 적군 삭제 및 초기화

    player.setPlayer("sky_my_unit.PNG", sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f));  // 아군 유닛 초기화

}

void Game::initWindow() {
   
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages"); // 윈도우 게임화면 렌더링
    // 전체 화면 (그래픽 볼 때 전체화면으로 미리 실행해보면 좋을 것 같아서 넣음)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);
    
    window->setFramerateLimit(60);  // 프레임 속도 제한, 초당 60프레임
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
                player.special_attack(); // E 키를 눌렀을 때 한 번만 호출
            }
        }
      
        // 숫자 입력에 따른 맵 전환 // 1: 하늘, 2: 바다, 3: 땅
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
            stageNumber = 1;

            currentStage.setStage(stageNumber, enemies);
            player.setPlayer("sky_my_unit.PNG", sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f));
            player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 9.0f / 10.0f));
            currentStage.spawnEnemies(enemies);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
            stageNumber = 2; 
            
            currentStage.setStage(stageNumber, enemies);
            player.setPlayer("sea_my_unit.PNG",sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f));
            player.setPosition(sf::Vector2f(WINDOWWIDTH / 4.0f, WINDOWHEIGHT / 2.0f));
            currentStage.spawnEnemies(enemies);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
            stageNumber = 3;

            currentStage.setStage(stageNumber, enemies);
            player.setPlayer("land_my_unit_right.PNG",sf::Vector2f(1.0f, 0.0f),sf::Vector2f(0.0f, -1.0f));
            player.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 4.0f * 3));
            currentStage.spawnEnemies(enemies);
        }

    
    }
}

void Game::update() { // 게임 상태 업데이트
    static sf::Clock attackClock; // 자동 발사 간격을 위한 시계
    float dt = clock.restart().asSeconds(); // 프레임 간 경과 시간 측정

    float speed = player.get_speed();
    float dx = 0.0f, dy = 0.0f;
    
    // 플레이어 움직임 업데이트
    dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
    dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;
    
    if (stageNumber == 3) dy = 0;
    else if (dx * dy) {  // 대각선 이동의 경우 좌우, 상하 단일 움직임 보다 빨라지는 속도를 보정
        dx *= 0.7;
        dy *= 0.7;
    }

    for (float i = 0; i < 1; i += dt) player.move(sf::Vector2f(dx * dt, dy * dt));


    // 200ms 간격으로 기본 공격 발사
    if (attackClock.getElapsedTime().asMilliseconds() >= 100) {
        player.basic_attack(); // 기본 공격 발사
        attackClock.restart();       // 타이머 초기화
    }

    player.updateAttack();


    // 적의 상태 업데이트 및 공격 수행
    for (auto* enemy : enemies) {
        //enemy->update(dt);  // 적 상태 업데이트 (필요 시)
           // 적의 공격 수행 (공격 타입에 따라)
    }



}

void Game::render() {
    window->clear(); // 화면 지우기

    currentStage.drawBackground(*window);

    // player.draw(playerSpeed * dt, 0);
     // 여기에서 게임 객체를 그리기 (예: player, enemy 등)
    player.draw(*window);
  
    player.renderAttack(*window);


    // 적 업데이트 및 화면에 그리기
    for (auto* enemy : enemies) {
        
        //enemy->attack();         // 적의 공격 수행
        enemy->draw(*window);     // 적을 화면에 그리기
    }

    window->display(); // 화면에 그린 내용을 표시
}
