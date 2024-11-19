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
        sprite.setScale(0.2f, 0.2f);  // 필요에 따라 스케일 조정
        sprite.setTexture(texture);   // 텍스처를 스프라이트에 적용
    }
}

void Enemy::updateDirection(int newDirection) {
    if (stageNumber == 3) { // 땅 스테이지에서만 동작
        if (newDirection != 0) {
            direction = newDirection; // 방향 설정
        }
    }
}

void Enemy::update(float deltaTime) {
    if (stageNumber == 1) { // 하늘 스테이지
        if (dynamic_cast<NormalUnit*>(this)) {
            position.y += 200.0f * deltaTime; // 아래로 직선 이동
        }
        else if (dynamic_cast<EliteUnit*>(this)) {
            // 목표값 도달 시 새로운 목표값 설정
            if (position.y + 1.0f >= nextTargetY) {
                targetX = rand() % (1200 - 600) + 450; // 새로운 랜덤 X 좌표
                if (nextTargetY == 600) nextTargetY += 500; 
                else nextTargetY += 150; // 다음 Y 목표값 증가
                std::cout << "New targetX: " << targetX << ", nextTargetY: " << nextTargetY << std::endl; // 디버그
            }
            // X축과 Y축 남은 거리 계산
            float deltaX = targetX - position.x; // X축 남은 거리
            float deltaY = nextTargetY - position.y; // Y축 남은 거리

            // 이동 속도 계산
            float xSpeed = deltaX / 0.7f; // X축 속도 (거리 / 시간)
            float ySpeed = deltaY / 0.7f; // Y축 속도 (거리 / 시간)

            // 최소 속도 유지
            float minSpeed = 60.0f; // 최소 속도
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // 속도를 최소값 이상으로 유지
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // 속도를 최소값 이상으로 유지
            }

            // 좌표 업데이트
            position.x += xSpeed * deltaTime; // 프레임당 X축 이동
            position.y += ySpeed * deltaTime; // 프레임당 Y축 이동
        }
    }
    else if (stageNumber == 2) { // 바다 스테이지
        if (dynamic_cast<NormalUnit*>(this)) {
            position.x -= 130.0f * deltaTime; // 왼쪽으로 직선 이동
        }
        else if (dynamic_cast<EliteUnit*>(this)) {
        //    // X 목표값에 도달하면 Y 목표값 설정
        //    if (position.x <= nextTargetX && nextTargetX > 750) { // 750까지만 갱신
        //        targetY = rand() % 900; // 새로운 랜덤 Y 좌표
        //        nextTargetX -= 150; // 다음 X 목표값 감소 (1200, 1050, 900, 750 구간)
        //    }

        //    // 목표 Y 좌표로 이동
        //    float speed = 100.0f; // Y축 이동 속도
        //    float direction = (targetY > position.y) ? 1.0f : -1.0f; // 방향 결정
        //    position.y += direction * speed * deltaTime;

        //    // 목표 좌표에 근접하면 Y 좌표 고정
        //    if (std::abs(targetY - position.y) < 1.0f) {
        //        position.y = targetY;
        //    }

        //    // X 방향으로는 계속 왼쪽으로 이동
        //    position.x -= 100.0f * deltaTime;
        //}// 목표값 도달 시 새로운 목표값 설정
            if (position.x - 1.0f <= nextTargetX) { // X축 목표값 도달 여부
                targetY = rand() % (800 - 200) + 200; // 새로운 랜덤 Y 좌표
                if (nextTargetX == 600) nextTargetX -= 500;
                else nextTargetX -= 150; // 다음 X 목표값 감소
                std::cout << "New targetY: " << targetY << ", nextTargetX: " << nextTargetX << std::endl; // 디버그
            }

            // X축과 Y축 남은 거리 계산
            float deltaX = nextTargetX - position.x; // X축 남은 거리
            float deltaY = targetY - position.y;    // Y축 남은 거리

            // 이동 속도 계산
            float xSpeed = deltaX / 0.7f; // X축 속도 (거리 / 시간)
            float ySpeed = deltaY / 0.7f; // Y축 속도 (거리 / 시간)

            // 최소 속도 유지
            float minSpeed = 60.0f; // 최소 속도
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // 속도를 최소값 이상으로 유지
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // 속도를 최소값 이상으로 유지
            }

            // 좌표 업데이트
            position.x += xSpeed * deltaTime; // 프레임당 X축 이동
            position.y += ySpeed * deltaTime; // 프레임당 Y축 이동
        }
    }
    else if (stageNumber == 3) { // 땅 스테이지
        if (dynamic_cast<NormalUnit*>(this)) {
            position.x += direction * 200.0f * deltaTime; // 방향에 따라 이동
        }
        else if (dynamic_cast<EliteUnit*>(this)) {
            position.x += direction * 100.0f * deltaTime; // 방향에 따라 이동
            position.y += std::cos(position.x / 50.0f) * 30.0f * deltaTime; // 위아래로 흔들리며 이동
        }
    }
}