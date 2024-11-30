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
        dt = clock.restart().asSeconds(); // ������ �� ��� �ð� ����
        handleEvents();
        //sf::Time deltaTime = clock.restart(); // ������ �� ��� �ð� ����  
        if (player.getHealth() <= 0) {
        }
        else update();
   
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

    uiManager.init();
}

void Game::initWindow() {
   
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages"); // ������ ����ȭ�� ������
    // ��ü ȭ�� (�׷��� �� �� ��üȭ������ �̸� �����غ��� ���� �� ���Ƽ� ����)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);
    
    window->setFramerateLimit(60);  // ������ �ӵ� ����, �ʴ� 60������

    // �߾� ���簢�� ������ ���� ���� �� �ʱ�ȭ
    gameView.setCenter(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f); // ȭ���� �߾� ����
    gameView.setSize(900, 900); // ��ü ȭ�� ũ�⸦ ����� ���簢�� �κи��� �� �� �ְ� ����

    // Viewport �������� �߾� 900x900 ������ �����ϵ��� ���� (â ũ�� ���� ���߱�)
    float viewportX = (WINDOWWIDTH - 900) / (2.0f * WINDOWWIDTH); // �¿� ���� ����
    float viewportY = 0.f; // ���� ���� ����
    float viewportWidth = 900.0f / WINDOWWIDTH; // �߾� ���� �ʺ� ����
    float viewportHeight = 1.0f; // ��ü ���� ���

    // Viewport ����
    gameView.setViewport(sf::FloatRect(viewportX, viewportY, viewportWidth, viewportHeight));

    // ��ü ȭ���� ���� UI �� �ʱ�ȭ
    uiView = window->getDefaultView(); // �⺻ ȭ�� ��ü ��
}

void Game::handleEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            isRunning = false;
            window->close();
        }
        // UIManager�� �̺�Ʈ ����
        uiManager.handleEvent(event);

        // UI�� ��Ŀ���� ���� ���� ���� �Է��� ó������ ����
        if (!uiManager.isInputFocused()) {
            // ���� �Է� ó�� (�������� ��ȯ ��)
            if (event.type == sf::Event::KeyPressed) {
                // �������� ��ȯ
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

                // Ư�� ���� �� ���� ��ȯ
                // ...
                if (event.type == sf::Event::KeyPressed) {   // �� �� ������ �� �� ���� �����ǵ��� Ű�� ���� ������ ��쿡�� ����
                    //  Ư�� ���� : E Ű�� ������ �� ����
                    if (event.key.code == sf::Keyboard::E) {
                        player.specialAttack(); // E Ű�� ������ �� �� ���� ȣ��
                    }
                    // �ʻ�� : Q Ű�� ������ �� ����
                    if (event.key.code == sf::Keyboard::Q) {
                        player.ultimateAttack(); // Q Ű�� ������ �� �� ���� ȣ��
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
            }
        }
    }
}


void Game::update() { // ���� ���� ������Ʈ
    if (player.getHealth() > 0) {
        // ����Ʈ ���� ų ���� ������Ʈ
        killInfo = ""; // ���ڿ� �ʱ�ȭ
        for (int stage = 1; stage <= 3; ++stage) {
            killInfo += std::to_string(eliteUnitKillCounts[stage]) + "\n";
        }
        eliteUnitKillText.setFont(font);
        eliteUnitKillText.setCharacterSize(38);
        eliteUnitKillText.setFillColor(sf::Color(100, 100, 100, 250));
        eliteUnitKillText.setPosition(1600, 290);
        eliteUnitKillText.setString(killInfo); // �ؽ�Ʈ ����

        static sf::Clock attackClock; // �ڵ� �߻� ������ ���� �ð�
        static sf::Clock allyAttackClock;

        // �÷��̾� ��Ÿ�� ������Ʈ
        player.updateCooldowns(dt);

        if (!uiManager.isInputFocused()) {
            float speed = player.getSpeed();
            float dx = 0.0f, dy = 0.0f;

            // �÷��̾� ������ ������Ʈ
            dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
            dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;

            if (stageNumber == 3) dy = 0; // �������� 3������ y�� �̵� �Ұ�
            else if (dx != 0 && dy != 0) { // �밢�� �̵� �ӵ� ����
                dx *= 0.7071f;
                dy *= 0.7071f;
            }

            // �÷��̾� �̵� ����
            for (float i = 0; i < 1; i += this->dt) player.move(sf::Vector2f(dx * dt, dy * dt));

        }

        // 200ms �������� �⺻ ���� �߻�
        if (attackClock.getElapsedTime().asMilliseconds() >= 100) {
            player.basicAttack(); // �⺻ ���� �߻�
            attackClock.restart(); // Ÿ�̸� �ʱ�ȭ
        }

        // ���������� ���� �Ʊ� ���� �߻� �ӵ� ����
        if (stageNumber == 1) {
            // �ϴ� ��������: 100ms �������� �߻�
            if (allyAttackClock.getElapsedTime().asMilliseconds() >= 100) {
                player.allyAttack(); // �Ʊ� ���� �⺻ ���� �߻�
                allyAttackClock.restart(); // Ÿ�̸� �ʱ�ȭ
            }
        }
        else if (stageNumber == 3) {
            // �� ��������: 500ms �������� �߻�
            if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
                player.allyAttack(); // �Ʊ� ���� �⺻ ���� �߻�
                allyAttackClock.restart(); // Ÿ�̸� �ʱ�ȭ
            }
        }

        // �Ʊ� ���� ������Ʈ
        player.updateAllies(dt);

        // �÷��̾� ���� ������Ʈ
        player.collision(enemies);
        player.updateAttack();

        // �� ���� �� ������Ʈ
        currentStage.spawnEnemies(enemies, dt);
        for (auto* enemy : enemies) {
            enemy->collision(player);
            enemy->update(dt);  // �� ���� ������Ʈ
            // ���� ���� ���� (���� �ʿ�)
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

        // UI ������Ʈ (���� ���� ��)
       uiManager.update(stageNumber, false);
    }
    else {
        // ���� ���� ���� ó��
        uiManager.update(stageNumber, true);
    }
}

void Game::render() {
    window->clear(); // ȭ�� �����

    window->setView(gameView); // ���� �� ���� (�߾� ���簢�� ����)

        // ��� �׸���
    currentStage.drawBackground(*window);

    // ���� ������Ʈ �׸���
    for (auto* enemy : enemies) {
        enemy->draw(*window);
    }

    player.renderAttack(*window);
    player.drawAllies(*window);
    window->setView(uiView); // UI �� ���� (��ü ȭ�� ����)

    // UI �׸���
    uiManager.render(*window);

    if (player.getHealth() <= 0) {
        // ���� ���� ȭ�� �׸���
        uiManager.drawGameOverScreen(*window);
    }
    player.draw(*window);


    window->display(); // ȭ�鿡 �׸� ������ ǥ��
}
