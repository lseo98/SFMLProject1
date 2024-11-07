#include "InputPlayerMoveKey.h"
#include<iostream>
//void playerMoveKey(Player &player, sf::Keyboard::Key keyCode) {
void playerMoveKey(Player &player, sf::Event event) {
	
	float speed = player.get_speed();
	float dx = 0.0f, dy = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dy -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dy += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dx -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dx += speed;
	}
	/*if (keyCode == 'w') {
		dy -= speed;
	}
	if (keyCode == 'a') {
		dx -= speed;
	}
	if (keyCode == 's') {
		dy += speed;
	}
	if (keyCode == 'd') {
		dx += speed;
	}*/
	player.move(sf::Vector2f(dx, dy));

}


