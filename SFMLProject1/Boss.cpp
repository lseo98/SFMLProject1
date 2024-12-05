#include "Boss.h"
#include <iostream>

Boss::Boss() : Enemy(3000.0f, 0.5f, sf::Vector2f(0, 0),4), phase(1) {
    // ������ �ʱ� ü���� 3000, �ӵ��� 0.5�� ����
    time = pattern1 = pattern2 = pattern3 = pattern4 = pattern5 = 0;

}

 

void Boss::change_phase() {
    if (health < 1500.0f && phase == 1) {
        phase = 2;
        std::cout << "������ 2�� ��ȯ\n";
    }
    else if (health < 500.0f && phase == 2) {
        phase = 3;
        std::cout << "������ 3���� ��ȯ\n";
    }
    // ü�¿� ���� ������ ������ ����
}

void Boss::attack(float deltaTime) {
    pattern2_Laser();
}
void Boss::updateAttack(float deltaTime) {

}

void Boss::render(sf::RenderWindow& window) {
    for (sf::RectangleShape *l : laser) {
        window.draw(*l);
    }
}



void Boss::pattern2_Laser() {
    
    pattern2 = 0;
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape *laserRectangle = new sf::RectangleShape(sf::Vector2f(150,900));

        laserRectangle->setFillColor(sf::Color(255, 0, 0, 127));
        sf::Vector2f laserPosition(0,0);
        srand(std::time(NULL));
        float x = rand() % 200 - 50;
        laserPosition.x = 200 * i + x;
        laserRectangle->setPosition(laserPosition);

        laser.push_back(laserRectangle);

    }
}