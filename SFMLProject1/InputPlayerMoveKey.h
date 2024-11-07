#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include <vector>

//void playerMoveKey(Player& player, sf::Keyboard::Key keyCode);
void playerMoveKey(Player& player, sf::Event event);