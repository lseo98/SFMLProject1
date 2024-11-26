#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(float health, float speed, sf::Vector2f position, int stageNumber) 
    : Character(health, speed, position), stageNumber(stageNumber){
}

void Enemy::takeDamage(float amount) {
    health -= amount;
    if (health < 0) health = 0;
    // EliteUnit인지 확인하고 카운트 증가
    if (dynamic_cast<EliteUnit*>(this)) {
        eliteUnitKillCounts[stageNumber]++; // 현재 스테이지의 카운트 증가
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
    //체력에 따른 체력량 표시
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
        sprite.setScale(0.15f, 0.15f);  // 필요에 따라 스케일 조정
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
                targetX = rand() % (1350 - 450) + 450; // 새로운 랜덤 X 좌표
                if (nextTargetY == 400) nextTargetY += 500; 
                else nextTargetY += 100; // 다음 Y 목표값 증가
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

            if (position.x <= 450 || position.x >= 1350) { // 벽 범위
                xSpeed = -xSpeed; // X축 속도 반전
                targetX = rand() % (1350 - 450) + 450; // 새로운 랜덤 X 좌표 설정
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
                targetY = rand() % 900; // 새로운 랜덤 Y 좌표
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

            // 상하 벽 충돌 처리
            if (position.y <= 0 || position.y >= 900) { // 벽 범위
                xSpeed = -xSpeed; // X축 속도 반전
                targetY = rand() % 900; // 새로운 랜덤 Y 좌표
            }
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

bool Enemy::isOffScreen() const {
    int centerX = WINDOWWIDTH / 2;
    int centerY = WINDOWHEIGHT / 2;
    int rangeX = 500;
    int rangeY = 500;

    return (position.x < centerX - rangeX || position.x > centerX + rangeX ||
        position.y < centerY - rangeY || position.y > centerY + rangeY);
}


// EliteUnit

void EliteUnit::special_attack() {
    if (!missileLaunched) {                                                 // 미사일이 없는 경우
        // 유닛의 중앙 위치를 계산하여 미사일의 시작 위치로 사용
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += width / 2.0f; // 플레이어의 중심 x 좌표
        missileStartPosition.y += height / 2.0f; // 플레이어의 중심 y 좌표
        missiles.emplace_back(new Missile(missileStartPosition, missileDirection, 1.0f)); 
        // missileLaunched = true;

    }
}

void EliteUnit::updateAttack() {
    
    for (Missile *missile : missiles) {
        missile->update(); // 발사체 상태 업데이트
    }
}

void EliteUnit::renderAttack(sf::RenderWindow& window) {

    for (Missile *missile : missiles) {
        missile->draw(window); // 발사체 상태 업데이트
    }

}