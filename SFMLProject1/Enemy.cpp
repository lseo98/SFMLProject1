#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(float health, float speed, sf::Vector2f position, int stageNumber) 
    : Character(health, speed, position), stageNumber(stageNumber), attackPattern(nullptr) {
}

void Enemy::setEnemyAttack(std::unique_ptr<EnemyAttack> pattern) {
    attackPattern = std::move(pattern);
}

void Enemy::attack() {
    if (attackPattern) attackPattern->attack_pattern();
}

void Enemy::take_damage(float amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Enemy::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}

void Enemy::image(const std::string& textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setScale(0.2f, 0.2f);  // �ʿ信 ���� ������ ����
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
            // ��ǥ�� ���� �� ���ο� ��ǥ�� ����
            if (position.y + 1.0f >= nextTargetY) {
                targetX = rand() % (1200 - 600) + 450; // ���ο� ���� X ��ǥ
                if (nextTargetY == 600) nextTargetY += 500; 
                else nextTargetY += 150; // ���� Y ��ǥ�� ����
                std::cout << "New targetX: " << targetX << ", nextTargetY: " << nextTargetY << std::endl; // �����
            }
            // X��� Y�� ���� �Ÿ� ���
            float deltaX = targetX - position.x; // X�� ���� �Ÿ�
            float deltaY = nextTargetY - position.y; // Y�� ���� �Ÿ�

            // �̵� �ӵ� ���
            float xSpeed = deltaX / 0.7f; // X�� �ӵ� (�Ÿ� / �ð�)
            float ySpeed = deltaY / 0.7f; // Y�� �ӵ� (�Ÿ� / �ð�)

            // �ּ� �ӵ� ����
            float minSpeed = 60.0f; // �ּ� �ӵ�
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
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
        //    // X ��ǥ���� �����ϸ� Y ��ǥ�� ����
        //    if (position.x <= nextTargetX && nextTargetX > 750) { // 750������ ����
        //        targetY = rand() % 900; // ���ο� ���� Y ��ǥ
        //        nextTargetX -= 150; // ���� X ��ǥ�� ���� (1200, 1050, 900, 750 ����)
        //    }

        //    // ��ǥ Y ��ǥ�� �̵�
        //    float speed = 100.0f; // Y�� �̵� �ӵ�
        //    float direction = (targetY > position.y) ? 1.0f : -1.0f; // ���� ����
        //    position.y += direction * speed * deltaTime;

        //    // ��ǥ ��ǥ�� �����ϸ� Y ��ǥ ����
        //    if (std::abs(targetY - position.y) < 1.0f) {
        //        position.y = targetY;
        //    }

        //    // X �������δ� ��� �������� �̵�
        //    position.x -= 100.0f * deltaTime;
        //}// ��ǥ�� ���� �� ���ο� ��ǥ�� ����
            if (position.x - 1.0f <= nextTargetX) { // X�� ��ǥ�� ���� ����
                targetY = rand() % (800 - 200) + 200; // ���ο� ���� Y ��ǥ
                if (nextTargetX == 600) nextTargetX -= 500;
                else nextTargetX -= 150; // ���� X ��ǥ�� ����
                std::cout << "New targetY: " << targetY << ", nextTargetX: " << nextTargetX << std::endl; // �����
            }

            // X��� Y�� ���� �Ÿ� ���
            float deltaX = nextTargetX - position.x; // X�� ���� �Ÿ�
            float deltaY = targetY - position.y;    // Y�� ���� �Ÿ�

            // �̵� �ӵ� ���
            float xSpeed = deltaX / 0.7f; // X�� �ӵ� (�Ÿ� / �ð�)
            float ySpeed = deltaY / 0.7f; // Y�� �ӵ� (�Ÿ� / �ð�)

            // �ּ� �ӵ� ����
            float minSpeed = 60.0f; // �ּ� �ӵ�
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // �ӵ��� �ּҰ� �̻����� ����
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