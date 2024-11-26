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
        sprite.setScale(0.13f, 0.13f);  // 필요에 따라 스케일 조정
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
            srand(rand());
            // 목표값 도달 시 새로운 목표값 설정
            if (position.y >= nextTargetY) {
                targetX = rand() % 800 + 450; // 새로운 랜덤 X 좌표
                if (nextTargetY == 600) nextTargetY += 350; 
                else nextTargetY += 100; // 다음 Y 목표값 증가
                //std::cout << "New targetX: " << targetX << ", nextTargetY: " << nextTargetY << std::endl; // 디버그
            }
            else if (position.y == -100) { // 초기 스폰 위치에서 목표값 설정
                targetX = rand() % 700 + 550; // 새로운 랜덤 X 좌표
            }
            // X축과 Y축 남은 거리 계산
            float deltaX = targetX - position.x; // X축 남은 거리
            float deltaY = nextTargetY - position.y; // Y축 남은 거리

            // 이동 속도 계산
            float xSpeed = deltaX / 0.8f; // X축 속도 
            float ySpeed = deltaY / 0.6f; // Y축 속도 

            // 최소 속도 유지
            float minSpeed = 50.0f; // 최소 속도
            if (fabs(xSpeed) < minSpeed) {
                xSpeed = (xSpeed > 0 ? 1 : -1) * minSpeed; // 속도를 최소값 이상으로 유지
            }
            if (fabs(ySpeed) < minSpeed) {
                ySpeed = (ySpeed > 0 ? 1 : -1) * minSpeed; // 속도를 최소값 이상으로 유지
            }

            if (position.x <= 450 || position.x >= 1350) { // 벽 범위
                xSpeed = -xSpeed; // X축 속도 반전
                targetX = rand() % 900 + 450; // 새로운 랜덤 X 좌표 설정
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
            srand(rand());
            // 목표값 도달 시 새로운 목표값 설정
            if (position.x <= nextTargetX) {
                targetY = rand() % 600 + 200; // 새로운 랜덤 Y 좌표
                if (nextTargetX == 300) nextTargetX -= 350;
                else nextTargetX -= 100; // 다음 X 목표값 
                //std::cout << "New targetY: " << targetY << ", nextTargetX: " << nextTargetX << std::endl; // 디버그
            }
            else if (position.x == 1400) { // 초기 스폰 위치에서 목표값 설정
                targetY = rand() % 600 + 200; // 새로운 랜덤 Y 좌표
            }
            // X축과 Y축 남은 거리 계산
            float deltaX = nextTargetX - position.x; // X축 남은 거리
            float deltaY = targetY - position.y;    // Y축 남은 거리

            // 이동 속도 계산
            float xSpeed = deltaX / 1.0f; // X축 속도 
            float ySpeed = deltaY / 1.5f; // Y축 속도

            // 최소 속도 유지
            float minSpeed = 10.0f; // 최소 속도
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
                targetY = rand() % 600 + 200; // 새로운 랜덤 Y 좌표
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