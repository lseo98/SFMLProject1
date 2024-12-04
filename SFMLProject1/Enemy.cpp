#include "Enemy.h"
#include "Player.h"
#include <cmath>
#include <iostream>


Enemy::Enemy(float health, float speed, sf::Vector2f position, int stageNumber) 
    : Character(health, speed, position), stageNumber(stageNumber){
    collisionFlag = false;
}


void Enemy::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);

    sf::RectangleShape rectangle(sf::Vector2f(100.0f, 13.0f));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(this->position.x+3, this->position.y - 14.0f);
    window.draw(rectangle);
    ////printf("%d", health);
    ////ü�¿� ���� ü�·� ǥ��
    //float a = this->getHealth() / 300.0f * 96.0f;
    //sf::RectangleShape rectangle1(sf::Vector2f(a, 9.0f));
    //rectangle1.setFillColor(sf::Color::Red);
    //rectangle1.setPosition(this->position.x + 2, this->position.y - 8.0f);
    //window.draw(rectangle1);


    // ü�¹��� ���� ���
    float maxHealth = dynamic_cast<EliteUnit*>(this) ? 300.0f : 100.0f; // ����Ʈ ����: 300, �Ϲ� ����: 100
    float healthBarWidth = (this->getHealth() / maxHealth) * 96.0f; // ü�¿� ����� ����

    // ü�¹� (������)
    sf::RectangleShape healthBar(sf::Vector2f(healthBarWidth+2, 11.0f));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(this->position.x + 4, this->position.y - 13.0f);
    window.draw(healthBar);

}

void Enemy::image(const std::string& textureFile, const sf::IntRect& textureRect) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setTexture(texture);   // �ؽ�ó�� ��������Ʈ�� ����
        // �ؽ�ó ������ ������ ��� �ش� ������ ���
        if (textureRect != sf::IntRect()) {
            sprite.setTextureRect(textureRect);
        }
        sprite.setScale(0.13f, 0.13f);  // �ʿ信 ���� ������ ����
    }
}


void Enemy::updateDirection(int newDirection) {
    if (stageNumber == 3) { // �� �������������� ����
        if (newDirection != 0) {
            direction = newDirection; // ���� ����
        }
    }
}

void Enemy::collision(Player& player) {

    if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) && !collisionFlag) { // �浹 �߻� ��
        player.takeDamage(1);
        player.changeHeartSprite();
        std::cout << "�÷��̾� ��� : " << player.getHealth() << std::endl;
        collisionFlag = true;
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
            float minSpeed = 60.0f; // �ּ� �ӵ�                                                                                                                                                                
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }

            if (position.x <= 450 || position.x >= 1350) { // �� ����
                xSpeed = -xSpeed; // X�� �ӵ� ����
                targetX = rand() % (1350 - 450) + 450; // ���ο� ���� X ��ǥ ����
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