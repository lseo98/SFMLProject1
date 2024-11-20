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
    window = nullptr;   // ������ �ʱ�ȭ
    isRunning = true;   
    isMaingameRunning = true;   // stage 1, 2, 3�� �ƴ� �̴ϰ��� Ȥ�� ȭ�� ��ȯ �߿��� false
    this->clock.restart(); // ���� �̴ϰ��� Ȥ�� ���� ���� ���� �� �ð� ����ϴ� ������ ���� �ʿ�
    stageNumber = 1;        // 1: �ϴ�, 2: �ٴ�, 3: ��
    currentStage.setStage(stageNumber, enemies);    // ���� �������� �ʱ�ȭ
    currentStage.spawnEnemies(enemies);             // ���� �������� ���� ���� �� �ʱ�ȭ
}

void Game::initWindow() {
   
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages"); // ������ ����ȭ�� ������
    // ��ü ȭ�� (�׷��� �� �� ��üȭ������ �̸� �����غ��� ���� �� ���Ƽ� ����)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);
    
    window->setFramerateLimit(60);  // ������ �ӵ� ����, �ʴ� 60������
}

void Game::run() {
    while (isRunning && window->isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // ������ �� ��� �ð� ����
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // â �ݰų� esc ���� ��� ���� ����
            isRunning = false;
            window->close();
        }
        //  Ư�� ���� : E Ű�� ������ �� ����
        if(event.type == sf::Event::KeyPressed) {   // �� �� ������ �� �� ���� �����ǵ��� Ű�� ���� ������ ��쿡�� ����
            if (event.key.code == sf::Keyboard::E) {
                player.special_attack(); // E Ű�� ������ �� �� ���� ȣ��
            }
        }
      
        // ���� �Է¿� ���� �� ��ȯ // 1: �ϴ�, 2: �ٴ�, 3: ��
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
            stageNumber = 1;

            currentStage.setStage(stageNumber, enemies);
            player.setPlayer("sky_my_unit.PNG", sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f));
            currentStage.spawnEnemies(enemies);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
            stageNumber = 2; 
            
            currentStage.setStage(stageNumber, enemies);
            player.setPlayer("sky_my_unit.PNG",sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f));
            currentStage.spawnEnemies(enemies);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
            stageNumber = 3;

            currentStage.setStage(stageNumber, enemies);
            player.setPlayer("sky_my_unit.PNG",sf::Vector2f(1.0f, 0.0f),sf::Vector2f(0.0f, -1.0f));
            currentStage.spawnEnemies(enemies);
        }

    
    }
}

void Game::update() { // ���� ���� ������Ʈ
    static sf::Clock attackClock; // �ڵ� �߻� ������ ���� �ð�
    float dt = clock.restart().asSeconds(); // ������ �� ��� �ð� ����

    float speed = player.get_speed();
    float dx = 0.0f, dy = 0.0f;
    
    // �÷��̾� ������ ������Ʈ
    dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
    dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;
    
    if (stageNumber == 3) dy = 0;
    else if (dx * dy) {  // �밢�� �̵��� ��� �¿�, ���� ���� ������ ���� �������� �ӵ��� ����
        dx *= 0.7;
        dy *= 0.7;
    }

    for (float i = 0; i < 1; i += dt) player.move(sf::Vector2f(dx * dt, dy * dt));

    // 200ms �������� �⺻ ���� �߻�
    if (attackClock.getElapsedTime().asMilliseconds() >= 200) {
        player.basic_attack(); // �⺻ ���� �߻�
        attackClock.restart();       // Ÿ�̸� �ʱ�ȭ
    }

    player.updateAttack();


    // ���� ���� ������Ʈ �� ���� ����
    for (auto* enemy : enemies) {
        //enemy->update(dt);  // �� ���� ������Ʈ (�ʿ� ��)
        enemy->attack();    // ���� ���� ���� (���� Ÿ�Կ� ����)
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

}

void Game::render() {
    window->clear(); // ȭ�� �����

    currentStage.drawBackground(*window);

    // player.draw(playerSpeed * dt, 0);
     // ���⿡�� ���� ��ü�� �׸��� (��: player, enemy ��)
    player.draw(*window);
  
    player.renderAttack(*window);


    // �� ������Ʈ �� ȭ�鿡 �׸���
    for (auto* enemy : enemies) {
        
        //enemy->attack();         // ���� ���� ����
        enemy->draw(*window);     // ���� ȭ�鿡 �׸���
    }

    window->display(); // ȭ�鿡 �׸� ������ ǥ��
}
