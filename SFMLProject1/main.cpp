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

    return 0;
}
