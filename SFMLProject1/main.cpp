#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include "Game.h"
#include <ctime> // time() �Լ� ���

int WINDOWWIDTH = 1800;    // �� �ʺ�
int WINDOWHEIGHT = 900;    // �� ����



int main() {   

    srand(static_cast<unsigned>(time(0))); // ���� �������� seed�� ���� �ð����� ����
    sf::Event event;

    Game game; 

    bool goodEnding = game.run();
    if (goodEnding) std::cout << "good" << std::endl;
    else  std::cout << "bad" << std::endl;



    return 0;
}
