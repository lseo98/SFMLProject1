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
    currentStage.setStage(stageNumber, player, enemies);    // ���� �������� �ʱ�ȭ
    currentStage.spawnEnemies(enemies);                     // ���� �������� ���� ���� �� �ʱ�ȭ
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
      //  Ư�� ���� : E Ű�� ������ �� ����
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            player.performSpecialAttack(); // Ư�� ���� �޼��� ȣ��
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
            stageNumber = 1;
            currentStage.setStage(stageNumber, player, enemies);
            currentStage.spawnEnemies(enemies);
        }
        // else if �� ��� ���� �Է��� ó�� �� ��. ���� �������� ��ȯ �䱸������ ����
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
    float dt = deltaTime.asSeconds(); // �и��� ������ ��ȯ 
    // ���� ���� ������Ʈ (��: �÷��̾� �̵�)
    // float dt = deltaTime.asSeconds();
    float speed = player.get_speed();
    float dx = 0.0f, dy = 0.0f;
   
    dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
    dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;
    
    if (dx * dy) {  // �밢�� �̵��� ��� �¿�, ���� ���� ������ ���� �������� �ӵ��� ����
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
    window->clear(); // ȭ�� �����

    currentStage.update(player, enemies, *window);
    // player.draw(playerSpeed * dt, 0);
     // ���⿡�� ���� ��ü�� �׸��� (��: player, enemy ��)
    player.draw(*window);
    // ���� ���� ������ ���� �߻�ü ������Ʈ �� �׸���
    if (player.getAttackStrategy()) {
        player.getAttackStrategy()->updateProjectiles(*window);
    }

    // �� ������Ʈ �� ȭ�鿡 �׸���
    for (auto* enemy : enemies) {
        enemy->attack();         // ���� ���� ����
        enemy->draw(*window);     // ���� ȭ�鿡 �׸���
    }


    window->display(); // ȭ�鿡 �׸� ������ ǥ��
}