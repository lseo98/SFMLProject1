#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "Game.h"
#include <ctime> // time() 함수 사용

int WINDOWWIDTH = 1800;    // 맵 너비
int WINDOWHEIGHT = 900;    // 맵 높이



int main() {   

    srand(static_cast<unsigned>(time(0))); // 난수 생성기의 seed를 현재 시간으로 설정
    sf::Event event;

    Game game; 

    bool goodEnding = game.run();
    if (goodEnding) std::cout << "good" << std::endl;
    else  std::cout << "bad" << std::endl;



    return 0;
}
