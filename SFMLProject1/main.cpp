#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "Game.h"

int WINDOWWIDTH = 1800;    // �� �ʺ�
int WINDOWHEIGHT = 900;    // �� ����

int main() {   

  
   

    //window.setVerticalSyncEnabled(true); // V-Sync Ȱ��ȭ  
   
    
   

    Game game;
    game.run();

    // ���� ����
    //while (window.isOpen()) {
    //    sf::Event event;

    //    while (window.pollEvent(event)) {
    //        

    //        //if (event.type == sf::Event::KeyPressed) playerMoveKey(player, event.key.code);
    //        playerMoveKey(player, event);

    //        
    //    }

    //    // ȭ�� �����
    //    window.clear();

    //    // stage�� update �޼��带 ���� �ڵ� ���� ����
    //    currentStage.update(player, enemies, window);
    //    
    //    //sf::sleep(sf::milliseconds(30));  // �ð� ������ �Լ� 0.03�� delay
    
    //}

   

    return 0;
}
