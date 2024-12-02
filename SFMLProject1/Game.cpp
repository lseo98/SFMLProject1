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
        dt = clock.restart().asSeconds(); // ������ �� ��� �ð� ����
        handleEvents();
        //sf::Time deltaTime = clock.restart(); // ������ �� ��� �ð� ����  
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
//        //sf::Time deltaTime = clock.restart(); // ������ �� ��� �ð� ����
//        dt = clock.restart().asSeconds(); // ������ �� ��� �ð� ����
//        handleEvents();
//        update();
//        render();
//    }
//}

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

    // ����Ʈ ���� ��� �ؽ�Ʈ �ʱ�ȭ
    eliteUnitKillText.setFont(font);
    eliteUnitKillText.setCharacterSize(24);
    eliteUnitKillText.setFillColor(sf::Color::White);
    eliteUnitKillText.setPosition(1375, 500); // ȭ�� ���� ��ġ
    eliteUnitKillText.setString("0"); // �ʱⰪ

    // ��Ʈ �ε�
    if (!font.loadFromFile("R2.ttc")) {
        std::cerr << "��Ʈ ������ �ε��� �� �����ϴ�." << std::endl;
    }

    // ���� ���� �ؽ�Ʈ ����
    gameover.setFont(font);
    gameover.setString("GAME OVER");
    gameover.setFillColor(sf::Color::Black);

    gameover.setCharacterSize(80);
    gameover.setFillColor(sf::Color::White);

    // �ؽ�Ʈ�� ȭ�� �߾ӿ� ��ġ��Ű�� ���� �߽����� ����
    sf::FloatRect textRect = gameover.getLocalBounds();
    gameover.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    gameover.setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f));


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

    // ���� �Է� ���� ����
    inputBoxl.setSize(sf::Vector2f(450, 900));
    inputBoxl.setPosition(0, 0);
    inputBoxl.setFillColor(sf::Color::Black);
    inputBoxl.setOutlineColor(sf::Color::Green);
    inputBoxl.setOutlineThickness(2);

    // ������ �Է� ���� ����
    inputBoxr.setSize(sf::Vector2f(450, 900));
    inputBoxr.setPosition(1350, 0);
    inputBoxr.setFillColor(sf::Color::Black);
    inputBoxr.setOutlineColor(sf::Color::Green);
    inputBoxr.setOutlineThickness(2);

    // ������ ���� ���� ����
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
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // â �ݰų� esc ���� ��� ���� ����
            isRunning = false;
            window->close();
        }
        
  
      
        // ���� �Է¿� ���� �� ��ȯ // 1: �ϴ�, 2: �ٴ�, 3: ��
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
            stageNumber = 1;
        }
        // ���콺 ��ư Ŭ�� �̺�Ʈ ó��
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (inputBoxl.getGlobalBounds().contains(mousePos) ||
                    inputBoxr.getGlobalBounds().contains(mousePos)) {
                    printf("in\n");
                    // �Է� ���ڸ� Ŭ���ϸ� ��Ŀ�� Ȱ��ȭ
                    isInputActive = true;
                    //  inputBox.setFillColor(sf::Color::Yellow); // ��Ŀ�� �� ���� ���� (���� ����)
                }
                // �ٸ� ���� Ŭ���ϸ� ��Ŀ�� ��Ȱ��ȭ
                else {
                    printf("out\n");
                    isInputActive = false;
                }
            }
        }
        // Ű���� �Է� ó��
        if (isInputActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') {

                // �齺���̽� ó��
                if (!userInput.empty()) {
                    userInput.pop_back();
                }
            }
            else if (event.text.unicode == '\r') {
                // ���� ó�� (�ʿ�� ����)
                userInput += "\n";

            }
            else if (event.text.unicode < 128) {
                // �Ϲ� ���� �Է�
                userInput += static_cast<char>(event.text.unicode);

            }
            //printf("dlskjf");
            inputText.setString(userInput);
        }
        //���� ���� Ŭ���ÿ��� �÷��̾� Ư�� ���� �� �������� ��ȯ ����
        if (!isInputActive) {

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

                currentStage.setStage(stageNumber, enemies);

            }


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

void Game::update() { // ���� ���� ������Ʈ
    if (player.getHealth() > 0) {

   
        // �Է� �ؽ�Ʈ ����
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

        for (int stage = 1; stage <= 3; ++stage) { // �������� 1, 2, 3 ��ȸ
            killInfo += std::to_string(eliteUnitKillCounts[stage]) + "\n";
        }
        eliteUnitKillText.setFont(font);
        eliteUnitKillText.setCharacterSize(38);
        eliteUnitKillText.setFillColor(sf::Color(100, 100, 100, 250));
        eliteUnitKillText.setPosition(1600, 290);

        static sf::Clock attackClock; // �ڵ� �߻� ������ ���� �ð�
        static sf::Clock allyAttackClock;

        // �÷��̾� ��Ÿ�� ������Ʈ
        player.updateCooldowns(dt); // ��Ÿ�� ������Ʈ �߰�
        if (!isInputActive) {
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

        player.updateAllies(dt);
        // �÷��̾� ���� ������Ʈ
        player.collision(enemies);
        player.updateAttack(enemies);



        // �� ���� �� ������Ʈ
        currentStage.spawnEnemies(enemies, dt);
        for (auto* enemy : enemies) {
            enemy->collision(player);
            enemy->update(dt);  // �� ���� ������Ʈ (�ʿ� ��)
            // ���� ���� ���� (���� Ÿ�Կ� ����)
        }
        /* if (attackClock.getElapsedTime().asMilliseconds() >= 500) {
             for (auto* enemy : enemies) {
                 enemy->collision(player);
             }
         }*/

        // ȭ�� �� �� ����
        deleteEnemy();
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

        window->draw(eliteUnitKillText);


        player.renderAttack(*window);
        player.drawAllies(*window);  // �Ʊ� ���� �׸��� �߰�


        // (2) UI �並 �����ϰ� UI ���� ��� �׸���
        window->setView(uiView); // UI �� ���� (��ü ȭ�� ����)


        //�Է»��°� �ؽ�Ʈ �׸���
        window->draw(inputBoxl);
        window->draw(inputBoxr);
        window->draw(smallBoxr);

        window->draw(inputText);
        window->draw(text);
        window->draw(skytext);
        window->draw(seatext);
        window->draw(landtext);
        window->draw(textbox);


        // �÷��̾� ���� �׸���
        player.draw(*window);
        if (player.getHealth() <= 0)
            window->draw(gameover);
    

    window->display(); // ȭ�鿡 �׸� ������ ǥ��
}


void Game::deleteEnemy() {
    // ȭ�� ������ �����ų� ä���� 0 ������ �� ����
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy* enemy) {
                if (enemy->isOffScreen() || enemy->getHealth() <= 0) {  
                    delete enemy; // �޸� ����
                    return true; // ���� ���
                }
                return false; // ���� ���
            }),
        enemies.end());
}