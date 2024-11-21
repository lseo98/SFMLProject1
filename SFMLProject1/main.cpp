#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "Game.h"


int WINDOWWIDTH = 1800;    // ∏  ≥ ∫Ò
int WINDOWHEIGHT = 900;    // ∏  ≥Ù¿Ã


int main() {   

    //window.setVerticalSyncEnabled(true); // V-Sync »∞º∫»≠

    Game game;
    game.run();   

    return 0;
}
