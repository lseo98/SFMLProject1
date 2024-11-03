#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Stages");

    Player player;
    std::vector<Enemy*> enemies;
    Stage currentStage;

    int stageNumber = 1;
    currentStage.setStage(stageNumber, player, enemies);
    currentStage.spawnEnemies(enemies);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                stageNumber = 1;
                currentStage.setStage(stageNumber, player, enemies);
                currentStage.spawnEnemies(enemies);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                stageNumber = 2;
                currentStage.setStage(stageNumber, player, enemies);
                currentStage.spawnEnemies(enemies);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                stageNumber = 3;
                currentStage.setStage(stageNumber, player, enemies);
                currentStage.spawnEnemies(enemies);
            }
        }

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
