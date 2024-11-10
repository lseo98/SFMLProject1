#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "InputPlayerMoveKey.h"


int WINDOWWIDTH = 900;    // 맵 너비
int WINDOWHEIGHT = 900;    // 맵 높이


int main() {   

    // 윈도우 게임화면 렌더링
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Game Stages");
    
    // 전체 화면 (그래픽 볼 때 전체화면으로 미리 실행해보면 좋을 것 같아서 넣음)
    //sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow window(desktopMode, "Game Stages", sf::Style::Fullscreen);

    //window.setVerticalSyncEnabled(true); // V-Sync 활성화
    window.setFramerateLimit(60); // V-Sync 대신 프레임 속도 제한 (60fps)

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
            // 창 닫기 버튼 혹은 Esc 누르면 종료
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            //if (event.type == sf::Event::KeyPressed) playerMoveKey(player, event.key.code);
            playerMoveKey(player, event);

            // 특수 공격: E 키를 눌렀을 때 수행
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                player.performSpecialAttack(); // 특수 공격 메서드 호출
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
        }

        // 화면 지우기
        window.clear();

        // stage의 update 메서드를 통해 자동 공격 수행
        currentStage.update(player, enemies, window);
        
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
