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
    
    int adj = -5;
    if (dynamic_cast<EliteUnit*>(this)) adj = 10;

    sf::RectangleShape rectangle(sf::Vector2f(80.0f, 6.0f));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition((this->position.x + sprite.getGlobalBounds().width/2) - 50 + adj, this->position.y - 14.0f);
    window.draw(rectangle);
    ////printf("%d", health);
    ////체력에 따른 체력량 표시
    //float a = this->getHealth() / 300.0f * 96.0f;
    //sf::RectangleShape rectangle1(sf::Vector2f(a, 9.0f));
    //rectangle1.setFillColor(sf::Color::Red);
    //rectangle1.setPosition(this->position.x + 2, this->position.y - 8.0f);
    //window.draw(rectangle1);


    float maxHealth;// = dynamic_cast<EliteUnit*>(this) ? 300.0f : 100.0f; // 엘리트 유닛: 300, 일반 유닛: 100
    if (dynamic_cast<NormalUnit*>(this)) maxHealth = maxHealth_NormalUnit;
    else if (dynamic_cast<EliteUnit*>(this)) maxHealth = maxHealth_EliteUnit;
    else if (dynamic_cast<HealUnit*>(this)) maxHealth = maxHealth_HealUnit;
    else if(dynamic_cast<Shield*>(this)) maxHealth = maxHealth_Shield;
    else maxHealth = 100.0f;

    float healthBarWidth = (this->getHealth() / maxHealth) * 76.0f; // 체력에 비례한 길이

    // 체력바 (빨간색)
    sf::RectangleShape healthBar(sf::Vector2f(healthBarWidth+2, 4.0f));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition((this->position.x + sprite.getGlobalBounds().width / 2) - 49 + adj, this->position.y - 13.0f);
    window.draw(healthBar);

}

void Enemy::image(const std::string& textureFile, const sf::IntRect& textureRect) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setTexture(texture);   // 텍스처를 스프라이트에 적용
        // 텍스처 영역이 지정된 경우 해당 영역만 사용
        if (textureRect != sf::IntRect()) {
            sprite.setTextureRect(textureRect);
        }
        sprite.setScale(0.13f, 0.13f);  // 필요에 따라 스케일 조정
    }
}


void Enemy::updateDirection(int newDirection) {
    if (stageNumber == 3) { // 땅 스테이지에서만 동작
        if (newDirection != 0) {
            direction = newDirection; // 방향 설정
        }
    }
}

void Enemy::collision(Player& player) {

    if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) && !collisionFlag) { // 충돌 발생 시
        player.takeDamage(1);
        player.changeHeartSprite();
        std::cout << "플레이어 목숨 : " << player.getHealth() << std::endl;
        collisionFlag = true;
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
            if (position.y >= nextTargetY && previousY < nextTargetY) {
                targetX = rand() % 800 + 450; // 새로운 랜덤 X 좌표
                if (nextTargetY == 600) nextTargetY += 300; 
                else if (nextTargetY == 900)  nextTargetY -= 100;
                else nextTargetY += 100; // 다음 Y 목표값 증가
                //std::cout << "New targetX: " << targetX << ", nextTargetY: " << nextTargetY << std::endl; // 디버그
            }
            else if (position.y <= nextTargetY && previousY > nextTargetY) {
                targetX = rand() % 800 + 450; // 새로운 랜덤 X 좌표
                if (nextTargetY == 300) nextTargetY -= 300;
                else if (nextTargetY == 0)  nextTargetY += 100;
                else nextTargetY -= 100; // 다음 Y 목표값 증가
                //std::cout << "New targetX: " << targetX << ", nextTargetY: " << nextTargetY << std::endl; // 디버그
            }
            else if (position.y == -50) { // 초기 스폰 위치에서 목표값 설정
                targetX = rand() % 700 + 550; // 새로운 랜덤 X 좌표
            }
            // X축과 Y축 남은 거리 계산
            float deltaX = targetX - position.x; // X축 남은 거리
            float deltaY = nextTargetY - position.y; // Y축 남은 거리

            // 이동 속도 계산
            float xSpeed = deltaX / 0.8f; // X축 속도 
            float ySpeed = deltaY / 0.6f; // Y축 속도 

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


            previousY = position.y;

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
            if (position.x <= nextTargetX && previousX > nextTargetX){
                targetY = rand() % 600 + 200; // 새로운 랜덤 Y 좌표
                if (nextTargetX == 750) nextTargetX -= 300;
                else if (nextTargetX == 450) nextTargetX += 100;
                else nextTargetX -= 100; // 다음 X 목표값 
                //std::cout << "New targetY: " << targetY << ", nextTargetX: " << nextTargetX << std::endl; // 디버그
            }
            else if (position.x >= nextTargetX && previousX < nextTargetX) {
                targetY = rand() % 600 + 200; // 새로운 랜덤 Y 좌표
                if (nextTargetX == 950) nextTargetX += 300;
                else if (nextTargetX == 1250) nextTargetX -= 100;
                else nextTargetX += 100; // 다음 X 목표값 
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


            // 상하 벽 충돌 처리
            if (position.y <= 0 || position.y >= 900) { // 벽 범위
                xSpeed = -xSpeed; // X축 속도 반전
                targetY = rand() % 600 + 200; // 새로운 랜덤 Y 좌표
            }

            previousX = position.x;

            // 좌표 업데이트
            position.x += xSpeed * deltaTime; // 프레임당 X축 이동
            position.y += ySpeed * deltaTime; // 프레임당 Y축 이동

        }
    }
    else if (stageNumber == 3 || stageNumber == 4) { // 땅 스테이지
        if (dynamic_cast<NormalUnit*>(this)) {
            position.x += direction * 200.0f * deltaTime; // 방향에 따라 이동
        }
        else if (dynamic_cast<EliteUnit*>(this) || dynamic_cast<HealUnit*>(this)) {
            if (position.x <= 450) {
                direction = 1; // 오른쪽으로 이동
            }
            else if (position.x >= 1250) {
                direction = -1; // 왼쪽으로 이동
            }
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
sf::Texture EliteUnit::missileTexture;
void EliteUnit::fireMissile(sf::Vector2f targetPosition, std::vector<std::unique_ptr<Missile>>& globalMissiles) {
    if (fireClock.getElapsedTime().asSeconds() >= 5.0f) {
        // 초기 방향 설정
        sf::Vector2f direction = targetPosition - this->position;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude != 0) {
            direction /= magnitude;
        }
        // 추적형 미사일 생성
        auto newMissile = std::make_unique<Missile>(this->position, direction, 3.0f);
        
		sf::IntRect textureRect; 
        if (!missileTexture.loadFromFile("missile_sky.png"));
		//missileTexture.loadFromFile("missile_sky.png"); //여기 수정해야함 static으로 빼던가 resourceManager 싱글톤 사용
        newMissile->setTexture(missileTexture, textureRect);
        // 미사일을 추적형으로 설정
        newMissile->setTarget(); // 플레이어 위치를 참조로 설정
        globalMissiles.push_back(std::move(newMissile)); // 전역 벡터에 추가
        //emplace_back 는 새로운 객체를 추가하는 거라 push_back이 더 적절
        //globalMissiles.emplace_back(newMissile); // 전역 벡터에 추가

        

        fireClock.restart();

    }
}

void EliteUnit::updateAttack(float deltaTime) {
    
    for (auto& missile : missiles) {
        missile->update(); // 발사체 상태 업데이트
    }
    // 화면 밖 미사일 삭제
    missiles.erase(
        std::remove_if(missiles.begin(), missiles.end(),
            [](std::unique_ptr<Missile>& missile) {
                if (missile->isOffScreen()) {
                    return true;
                }
                return false;
            }),
        missiles.end());

    // 재발사 가능 상태로 전환 (예: 1초 후)
    if (fireClock.getElapsedTime().asSeconds() >= 5.0f) {
        fireClock.restart();
    }
}


void EliteUnit::renderAttack(sf::RenderWindow& window) {

    for (auto& missile : missiles) {
        missile->draw(window); // 발사체 상태 업데이트
    }

}