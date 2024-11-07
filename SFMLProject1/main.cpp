#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "InputPlayerMoveKey.h"


int WINDOWWIDTH = 1900;    // 맵 너비
int WINDOWHEIGHT = 980;    // 맵 높이
 
// a;ldskjf

int main() {   

    // 윈도우 게임화면 렌더링
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages");

    // 초기 객체 생성 및 초기화
    Player player;
    std::vector<Enemy*> enemies;
    Stage currentStage;

    int stageNumber = 1;        // 1: 하늘, 2: 바다, 3: 땅
    currentStage.setStage(stageNumber, player, enemies);
    currentStage.spawnEnemies(enemies);

    // 게임 루프
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
            // else if 의 경우 동시 입력이 처리 안 됨. 따라서 스테이지 전환 요구에서는 적절
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
        
        //sf::sleep(sf::milliseconds(30));  // 시간 딜레이 함수 0.03초 delay
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
