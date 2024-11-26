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
        //sf::Time deltaTime = clock.restart(); // ������ �� ��� �ð� ����
        dt = clock.restart().asSeconds(); // ������ �� ��� �ð� ����
        handleEvents();
        update();
        render();
    }
}

void Game::initVariables() {
    window = nullptr;   // ������ �ʱ�ȭ
    isRunning = true;   
    isMaingameRunning = true;   // stage 1, 2, 3�� �ƴ� �̴ϰ��� Ȥ�� ȭ�� ��ȯ �߿��� false
    this->clock.restart(); // ���� �̴ϰ��� Ȥ�� ���� ���� ���� �� �ð� ����ϴ� ������ ���� �ʿ�
    stageNumber = 1;        // 1: �ϴ�, 2: �ٴ�, 3: ��

    currentStage.setStage(stageNumber, enemies);    // ���� �������� �ʱ�ȭ
    currentStage.spawnEnemies(enemies, dt);             // ���� �������� ���� ���� �� �ʱ�ȭ

    player.setPlayer(stageNumber);  // �Ʊ� ���� �ʱ�ȭ


    currentStage.setStage(stageNumber, enemies);    // ���� �������� �ʱ�ȭ

}

void Game::initWindow() {
   
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages"); // ������ ����ȭ�� ������
    // ��ü ȭ�� (�׷��� �� �� ��üȭ������ �̸� �����غ��� ���� �� ���Ƽ� ����)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);
    
    window->setFramerateLimit(60);  // ������ �ӵ� ����, �ʴ� 60������
}




void Game::handleEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // â �ݰų� esc ���� ��� ���� ����
            isRunning = false;
            window->close();
        }
        
        if(event.type == sf::Event::KeyPressed) {   // �� �� ������ �� �� ���� �����ǵ��� Ű�� ���� ������ ��쿡�� ����
            //  Ư�� ���� : E Ű�� ������ �� ����
            if (event.key.code == sf::Keyboard::E) {
                player.special_attack(); // E Ű�� ������ �� �� ���� ȣ��
            }
            // �÷��̾� �¿� ����
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
      
        // ���� �Է¿� ���� �� ��ȯ // 1: �ϴ�, 2: �ٴ�, 3: ��
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

            currentStage.setStage(stageNumber,enemies);
        }    

    }
}

void Game::update() { // ���� ���� ������Ʈ
    static sf::Clock attackClock; // �ڵ� �߻� ������ ���� �ð�

    float speed = player.getSpeed();
    float dx = 0.0f, dy = 0.0f;
    
    // �÷��̾� ������ ������Ʈ
    dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
    dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;
    
    if (stageNumber == 3) dy = 0;
    else if (dx * dy) {  // �밢�� �̵��� ��� �¿�, ���� ���� ������ ���� �������� �ӵ��� ����
        dx *= 0.7;
        dy *= 0.7;
    }

    for (float i = 0; i < 1; i += this->dt) player.move(sf::Vector2f(dx * dt, dy * dt));

       

    // 200ms �������� �⺻ ���� �߻�
    if (attackClock.getElapsedTime().asMilliseconds() >= 100) {
        player.basic_attack(); // �⺻ ���� �߻�
        attackClock.restart(); // Ÿ�̸� �ʱ�ȭ
    }

    player.updateAttack(enemies);



    // �� ���� �� ������Ʈ
    currentStage.spawnEnemies(enemies, dt);
    for (auto* enemy : enemies) {
        enemy->update(dt);  // �� ���� ������Ʈ (�ʿ� ��)
        // ���� ���� ���� (���� Ÿ�Կ� ����)
    }
    // ȭ�� �� �� ����
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy* enemy) {
                if (enemy->isOffScreen()) {
                    delete enemy; // �޸� ����
                    return true; // ���� ���
                }
                return false; // ���� ���
            }),
        enemies.end());

}

void Game::render() {
    window->clear(); // ȭ�� �����

    // ��� �׸���
    currentStage.drawBackground(*window);

    // �÷��̾� ���� �׸���
    player.draw(*window);
    player.renderAttack(*window);



    // �� ���� �׸���
    for (auto* enemy : enemies) {
        enemy->draw(*window);     // ���� ȭ�鿡 �׸���
    }

    window->display(); // ȭ�鿡 �׸� ������ ǥ��
}
