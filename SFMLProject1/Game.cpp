#include "Game.h"
#include <iostream>

// ���� ��� ����
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
        dt = clock.restart().asSeconds(); // ������ �� ��� �ð� ����
        handleEvents();
        //sf::Time deltaTime = clock.restart(); // ������ �� ��� �ð� ����  
      //  std::cout << player.getHealth() << std::endl;
        if (player.getHealth() <= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                player.restart();
                stageNumber = 1;
                for (Enemy* enemy : enemies) {
                    delete enemy;
                }
                enemies.clear();
                for (auto& enemyMissile : enemyMissiles) {
                    //delete enemyMissile;
                }
                enemyMissiles.clear();
                currentStage.setStage(1, enemies);
            }
        }
        else update();

        render();
    }
}


void Game::initVariables() {
    globalClock.restart(); // ���� ���� �� Clock �ʱ�ȭ

    window = nullptr;   // ������ �ʱ�ȭ
    isRunning = true;   
    isMaingameRunning = true;   // stage 1, 2, 3�� �ƴ� �̴ϰ��� Ȥ�� ȭ�� ��ȯ �߿��� false
    this->clock.restart(); // ���� �̴ϰ��� Ȥ�� ���� ���� ���� �� �ð� ����ϴ� ������ ���� �ʿ�
    stageNumber = 1;        // 1: �ϴ�, 2: �ٴ�, 3: ��

    currentStage.setStage(stageNumber, enemies);    // ���� �������� �ʱ�ȭ
    currentStage.spawnEnemies(enemies, dt);             // ���� �������� ���� ���� �� �ʱ�ȭ

    player.setPlayer(stageNumber);  // �Ʊ� ���� �ʱ�ȭ

	uiManager.init(); // UI �ʱ�ȭ

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
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // â �ݰų� esc ���� ��� ���� ����
            isRunning = false;
            window->close();
        }
        
        // UIManager�� �̺�Ʈ ����
        uiManager.handleEvent(event,*window);
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
                    enemyMissiles.clear();
                    currentStage.spawnEnemies(enemies, dt);
                }
                // �ٸ� ���� Ŭ���ϸ� ��Ŀ�� ��Ȱ��ȭ
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
                    // ���� ���� �׽�Ʈ�� // �̰� ��� �� game update�� ���� boss.attack �ּ�ó���ؾ�
                    if (event.key.code == sf::Keyboard::T) {
                        if (stageNumber == 4) boss.attack(dt);
                    }
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

void Game::update() { // ���� ���� ������Ʈ
    if (player.getHealth() > 0) {
        // �Է� �ؽ�Ʈ ����

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
        // �ñر� ��Ÿ�� ���� ���
        float remainingUltimateCooldown = player.getUltimateAttackRemainingCooldown();
        float ultimateCooldownRatio = remainingUltimateCooldown / 20.0f;
        // Ư�� ���� ��Ÿ�� ���� ���
        float remainingSpecialCooldown = player.getSpecialAttackRemainingCooldown();
        float specialCooldownRatio = remainingSpecialCooldown / 5.0f;
        uiManager.setCooldownRatios(ultimateCooldownRatio, specialCooldownRatio);
        if (!uiManager.isInputFocused()) {
            float speed = player.getSpeed();
            float dx = 0.0f, dy = 0.0f;

            // �÷��̾� ������ ������Ʈ
            dx += (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)) * speed;
            dy += (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)) * speed;

            if (stageNumber == 3 || stageNumber == 4) dy = 0; // �������� 3������ y�� �̵� �Ұ�
            else if (dx != 0 && dy != 0) { // �밢�� �̵� �ӵ� ����
                dx *= 0.7071f;
                dy *= 0.7071f;
            }

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
        //else if (stageNumber == 2) {
        //    // �ٴ� ��������: 500ms �������� �߻�
        //    if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
        //        player.allyAttack(); // �Ʊ� ���� �⺻ ���� �߻�
        //        allyAttackClock.restart(); // Ÿ�̸� �ʱ�ȭ
        //    }
        //}
        else if (stageNumber == 3) {
            // �� ��������: 500ms �������� �߻�
            if (allyAttackClock.getElapsedTime().asMilliseconds() >= 500) {
                player.allyAttack(); // �Ʊ� ���� �⺻ ���� �߻�
                allyAttackClock.restart(); // Ÿ�̸� �ʱ�ȭ
            }
        }

        player.updateAllies(dt, enemies, enemyMissiles);
        // �÷��̾� ���� ������Ʈ
        player.collision(enemies);
        player.updateAttack();

        // �÷��̾� ������Ʈ
        player.updateBlink(); // ������ ���� ������Ʈ

        sf::Vector2f playerPosition = player.getPosition(); // �÷��̾� ��ġ ��������

        // �� ���� �� ������Ʈ
        currentStage.spawnEnemies(enemies, dt);
        for (auto* enemy : enemies) {
            enemy->collision(player);
            enemy->update(dt);  

            if (EliteUnit* elite = dynamic_cast<EliteUnit*>(enemy)) {
                elite->fireMissile(player.getPosition(), enemyMissiles); // �÷��̾ ��ǥ�� �̻��� �߻�
                // ���� ������ �̻����� ��� ������Ʈ
                /*if (!enemyMissiles.empty()) {
                    enemyMissiles.back()->update(); // ��� �߰��� �̻����� �ٷ� ������Ʈ
                }*/
            }
        }

        player.enemyProjectileCollision(enemyMissiles); // ���� ����ü�� �÷��̾�, �÷��̾� ����ü �� �浿 ó��
        enemyMissiles.erase(                            // �浹 �� ���� ����ü ����
            std::remove_if(enemyMissiles.begin(), enemyMissiles.end(),
                [](std::unique_ptr<Missile>& missile) {
                    return missile->checkCrashed();
                }),
            enemyMissiles.end()
        );


        for (auto& enemyMissile : enemyMissiles) { 
            enemyMissile->update(player.getPosition());
        }

        //// ȭ�� �� �̻��� ����
        //enemyMissiles.erase(
        //    std::remove_if(enemyMissiles.begin(), enemyMissiles.end(),
        //        [](Missile* missile) {
        //            return missile->isOffScreen();
        //        }),
        //    enemyMissiles.end()
        //);

        //sf::Vector2f playerPosition = player.getPosition(); // �÷��̾� ��ġ ��������

        //// �� �̻��� �߻�
        //for (auto* enemy : enemies) {
        //    enemy->fireMissile(enemyMissiles, playerPosition); // �÷��̾ ��ǥ�� �̻��� �߻�
        //}

        //// �� �̻��� ������Ʈ
        //for (auto* missile : enemyMissiles) {
        //    missile->targeting(playerPosition); // �÷��̾ ���� �̵�
        //}

        /* if (attackClock.getElapsedTime().asMilliseconds() >= 500) {
             for (auto* enemy : enemies) {
                 enemy->collision(player);
             }
         }*/

         // stage 4 ���� ���� ���� ó��
        if (stageNumber == 4) {
            //boss.attack(dt);
            boss.updateAttack(dt, player);
        }

        // ȭ�� �� �� ����
        deleteEnemy();
        uiManager.update(stageNumber, false);
    }
    else {
        // ���� ���� ���� ó��
        uiManager.update(stageNumber, true);
    }

}

void Game::render() {
    window->clear(); // ȭ�� �����

    // (1) ���� �並 �����ϰ� ���� ���� ��� �׸���
    window->setView(gameView); // ���� �� ���� (�߾� ���簢�� ����)

    // ��� �׸���
    currentStage.drawBackground(*window);


    // �� ���� �׸���
    for (auto* enemy : enemies) {
        enemy->draw(*window);     // ���� ȭ�鿡 �׸���
    }

    // �� �̻��� ������
    for (auto& missile : enemyMissiles) {
        missile->draw(*window);
    }

        

        
    //�Է»��°� �ؽ�Ʈ �׸���
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
    if (stageNumber == 4) boss.render(*window);

    window->display(); // ȭ�鿡 �׸� ������ ǥ��
}


void Game::deleteEnemy() {
    
    // ȭ�� ������ �����ų� ä���� 0 ������ �� ����
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [this](Enemy* enemy) {
                if (enemy->isOffScreen()) {  
                    delete enemy; // �޸� ����
                    return true; // ���� ���
                }
                else if(enemy->getHealth() <= 0) {  // ���� ���� ���� �� 
                    if (dynamic_cast<NormalUnit*>(enemy) == enemy) this->player.countKillNormal();
                    else if (dynamic_cast<EliteUnit*>(enemy) == enemy) this->player.countKillElite();
                    delete enemy; // �޸� ����
                    return true; // ���� ���
                }
                return false; // ���� ���
            }),
        enemies.end());
    
    // ȭ�� �� �̻��� ����
    enemyMissiles.erase(
        std::remove_if(enemyMissiles.begin(), enemyMissiles.end(),
            [](std::unique_ptr<Missile>& missile) {
                return missile->isOffScreen();
            }),
        enemyMissiles.end()
    );
}