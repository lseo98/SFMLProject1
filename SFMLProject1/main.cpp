#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "InputPlayerMoveKey.h"


int WINDOWWIDTH = 900;    // �� �ʺ�
int WINDOWHEIGHT = 900;    // �� ����


int main() {   

    // ������ ����ȭ�� ������
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages");
    
    // ��ü ȭ�� (�׷��� �� �� ��üȭ������ �̸� �����غ��� ���� �� ���Ƽ� ����)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);

    //window.setVerticalSyncEnabled(true); // V-Sync Ȱ��ȭ
    window.setFramerateLimit(60); // V-Sync ��� ������ �ӵ� ���� (60fps)

    // �ʱ� ��ü ���� �� �ʱ�ȭ
    Player player;
    std::vector<Enemy*> enemies;
    Stage currentStage;


    int stageNumber = 1;        // 1: �ϴ�, 2: �ٴ�, 3: ��
    currentStage.setStage(stageNumber, player, enemies);
    currentStage.spawnEnemies(enemies);

    // ���� ����
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            // â �ݱ� ��ư Ȥ�� Esc ������ ����
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            //if (event.type == sf::Event::KeyPressed) playerMoveKey(player, event.key.code);
            playerMoveKey(player, event);

            // Ư�� ����: E Ű�� ������ �� ����
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

        // ȭ�� �����
        window.clear();

        // stage�� update �޼��带 ���� �ڵ� ���� ����
        currentStage.update(player, enemies, window);
        
        //sf::sleep(sf::milliseconds(30));  // �ð� ������ �Լ� 0.03�� delay
        window.clear();
        player.draw(window);
        for (auto* enemy : enemies) {
            enemy->draw(window);
            enemy->attack();
        }
        window.display();
    }

    for (auto* enemy : enemies) {
        delete enemy;
    }

    return 0;
}
