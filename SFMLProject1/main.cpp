#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "InputPlayerMoveKey.h"


int WINDOWWIDTH = 1900;    // �� �ʺ�
int WINDOWHEIGHT = 980;    // �� ����
 
// a;ldskjf

int main() {   

    // ������ ����ȭ�� ������
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages");

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
            if (event.type == sf::Event::Closed) {
                window.close();
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


            //if (event.type == sf::Event::KeyPressed) playerMoveKey(player, event.key.code);
            playerMoveKey(player, event);
             

        }
        
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
