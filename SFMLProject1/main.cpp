#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "Game.h"

int WINDOWWIDTH = 1800;    // 맵 너비
int WINDOWHEIGHT = 900;    // 맵 높이

int main() {   

  
   

    //window.setVerticalSyncEnabled(true); // V-Sync 활성화  
   
    
   

    Game game;
    game.run();

    // 게임 루프
    //while (window.isOpen()) {
    //    sf::Event event;

    //    while (window.pollEvent(event)) {
    //        

    //        //if (event.type == sf::Event::KeyPressed) playerMoveKey(player, event.key.code);
    //        playerMoveKey(player, event);

    //        
    //    }

    //    // 화면 지우기
    //    window.clear();

    //    // stage의 update 메서드를 통해 자동 공격 수행
    //    currentStage.update(player, enemies, window);
    //    
    //    //sf::sleep(sf::milliseconds(30));  // 시간 딜레이 함수 0.03초 delay
    
    //}

   

    return 0;
}
