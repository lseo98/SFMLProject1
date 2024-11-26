#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(float health, float speed, sf::Vector2f position, int stageNumber) 
    : Character(health, speed, position), stageNumber(stageNumber){
}

void Enemy::takeDamage(float amount) {
    health -= amount;
    if (health < 0) health = 0;
    // EliteUnit���� Ȯ���ϰ� ī��Ʈ ����
    if (dynamic_cast<EliteUnit*>(this)) {
        eliteUnitKillCounts[stageNumber]++; // ���� ���������� ī��Ʈ ����
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);

    sf::RectangleShape rectangle(sf::Vector2f(100.0f, 13.0f));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(this->position.x, this->position.y - 10.0f);
    window.draw(rectangle);
    //printf("%d", health);
    //ü�¿� ���� ü�·� ǥ��
    float a = this->getHealth() / 300.0f * 96.0f;
    sf::RectangleShape rectangle1(sf::Vector2f(a, 9.0f));
    rectangle1.setFillColor(sf::Color::Red);
    rectangle1.setPosition(this->position.x +2, this->position.y - 8.0f);
    window.draw(rectangle1);
}

void Enemy::image(const std::string& textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setScale(0.13f, 0.13f);  // �ʿ信 ���� ������ ����
        sprite.setTexture(texture);   // �ؽ�ó�� ��������Ʈ�� ����
    }
}


void Enemy::updateDirection(int newDirection) {
    if (stageNumber == 3) { // �� �������������� ����
        if (newDirection != 0) {
            direction = newDirection; // ���� ����
        }
    }
}

void Enemy::update(float deltaTime) {
    if (stageNumber == 1) { // �ϴ� ��������
        if (dynamic_cast<NormalUnit*>(this)) {
            position.y += 200.0f * deltaTime; // �Ʒ��� ���� �̵�
        }
        else if (dynamic_cast<EliteUnit*>(this)) {
            srand(rand());
            // ��ǥ�� ���� �� ���ο� ��ǥ�� ����
            if (position.y >= nextTargetY) {
                targetX = rand() % 800 + 450; // ���ο� ���� X ��ǥ
                if (nextTargetY == 600) nextTargetY += 350; 
                else nextTargetY += 100; // ���� Y ��ǥ�� ����
                //std::cout << "New targetX: " << targetX << ", nextTargetY: " << nextTargetY << std::endl; // �����
            }
            else if (position.y == -100) { // �ʱ� ���� ��ġ���� ��ǥ�� ����
                targetX = rand() % 700 + 550; // ���ο� ���� X ��ǥ
            }
            // X��� Y�� ���� �Ÿ� ���
            float deltaX = targetX - position.x; // X�� ���� �Ÿ�
            float deltaY = nextTargetY - position.y; // Y�� ���� �Ÿ�

            // �̵� �ӵ� ���
            float xSpeed = deltaX / 0.8f; // X�� �ӵ� 
            float ySpeed = deltaY / 0.6f; // Y�� �ӵ� 

            // �ּ� �ӵ� ����
            float minSpeed = 50.0f; // �ּ� �ӵ�
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }

            if (position.x <= 450 || position.x >= 1350) { // �� ����
                xSpeed = -xSpeed; // X�� �ӵ� ����
                targetX = rand() % 900 + 450; // ���ο� ���� X ��ǥ ����
            }
            // ��ǥ ������Ʈ
            position.x += xSpeed * deltaTime; // �����Ӵ� X�� �̵�
            position.y += ySpeed * deltaTime; // �����Ӵ� Y�� �̵�
            
        }
    }
    else if (stageNumber == 2) { // �ٴ� ��������
        if (dynamic_cast<NormalUnit*>(this)) {
            position.x -= 130.0f * deltaTime; // �������� ���� �̵�
        }
        else if (dynamic_cast<EliteUnit*>(this)) {
            srand(rand());
            // ��ǥ�� ���� �� ���ο� ��ǥ�� ����
            if (position.x <= nextTargetX) {
                targetY = rand() % 600 + 200; // ���ο� ���� Y ��ǥ
                if (nextTargetX == 300) nextTargetX -= 350;
                else nextTargetX -= 100; // ���� X ��ǥ�� 
                //std::cout << "New targetY: " << targetY << ", nextTargetX: " << nextTargetX << std::endl; // �����
            }
            else if (position.x == 1400) { // �ʱ� ���� ��ġ���� ��ǥ�� ����
                targetY = rand() % 600 + 200; // ���ο� ���� Y ��ǥ
            }
            // X��� Y�� ���� �Ÿ� ���
            float deltaX = nextTargetX - position.x; // X�� ���� �Ÿ�
            float deltaY = targetY - position.y;    // Y�� ���� �Ÿ�

            // �̵� �ӵ� ���
            float xSpeed = deltaX / 1.0f; // X�� �ӵ� 
            float ySpeed = deltaY / 1.5f; // Y�� �ӵ�

            // �ּ� �ӵ� ����
            float minSpeed = 10.0f; // �ּ� �ӵ�
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }

            // ��ǥ ������Ʈ
            position.x += xSpeed * deltaTime; // �����Ӵ� X�� �̵�
            position.y += ySpeed * deltaTime; // �����Ӵ� Y�� �̵�

            // ���� �� �浹 ó��
            if (position.y <= 0 || position.y >= 900) { // �� ����
                xSpeed = -xSpeed; // X�� �ӵ� ����
                targetY = rand() % 600 + 200; // ���ο� ���� Y ��ǥ
            }
            // ��ǥ ������Ʈ
            position.x += xSpeed * deltaTime; // �����Ӵ� X�� �̵�
            position.y += ySpeed * deltaTime; // �����Ӵ� Y�� �̵�

        }
    }
    else if (stageNumber == 3) { // �� ��������
        if (dynamic_cast<NormalUnit*>(this)) {
            position.x += direction * 200.0f * deltaTime; // ���⿡ ���� �̵�
        }
        else if (dynamic_cast<EliteUnit*>(this)) {
            position.x += direction * 100.0f * deltaTime; // ���⿡ ���� �̵�
            position.y += std::cos(position.x / 50.0f) * 30.0f * deltaTime; // ���Ʒ��� ��鸮�� �̵�
        }
    }

}

bool Enemy::isOffScreen() const {
    int centerX = WINDOWWIDTH / 2;
    int centerY = WINDOWHEIGHT / 2;
    int rangeX = 600;
    int rangeY = 600;
    
    return (position.x < centerX - rangeX || position.x > centerX + rangeX ||
        position.y < centerY - rangeY || position.y > centerY + rangeY);
}


// EliteUnit

void EliteUnit::special_attack() {
    if (!missileLaunched) {                                                 // �̻����� ���� ���
        // ������ �߾� ��ġ�� ����Ͽ� �̻����� ���� ��ġ�� ���
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += width / 2.0f; // �÷��̾��� �߽� x ��ǥ
        missileStartPosition.y += height / 2.0f; // �÷��̾��� �߽� y ��ǥ
        missiles.emplace_back(new Missile(missileStartPosition, missileDirection, 1.0f)); 
        // missileLaunched = true;

    }
}

void EliteUnit::updateAttack() {
    
    for (Missile *missile : missiles) {
        missile->update(); // �߻�ü ���� ������Ʈ
    }
}

void EliteUnit::renderAttack(sf::RenderWindow& window) {

    for (Missile *missile : missiles) {
        missile->draw(window); // �߻�ü ���� ������Ʈ
    }

}