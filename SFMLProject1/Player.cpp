#include "Player.h"
#include "Bullet.h" 
#include "Missile.h"
#include <iostream>  

extern int WINDOWWIDTH, WINDOWHEIGHT;
// health,  speed, sf::Vector2f position
Player::Player() : Character(5, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 9.0f / 10.0f)) {
    //missileLaunched = false; 

    // 특수 공격 관련 변수 초기화
    specialAttackCooldown = 1.0f; // 특수 공격 쿨타임: 1초
    timeSinceLastSpecial = specialAttackCooldown; // 게임 시작 시 바로 사용할 수 있도록 설정
    canSpecialAttack = true;

    ultimateAttackCooldown = 20.0f; // 필살기 쿨타임 20초
    canUltimateAttack = true;

    waitTime = 0.0f; // 초기화

    killCountNomalUnit = 0;
    killCountEliteUnit1 = 0;
    killCountEliteUnit2 = 0;
    killCountEliteUnit3 = 0;


    initializeHearts();
}



void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // 위치 업데이트

    if (stageNumber == 1 || stageNumber == 3 || stageNumber == 4) {
        // 플레이어가 설정 화면 바깥으로 나갈 경우 예외 처리
        if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
        if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width;
        if (this->position.y < 0)  this->position.y = 0;
        if (this->position.y + height > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - height;
    }
    else if (stageNumber == 2) {
        // 플레이어가 점점 가라앉음
        this->position.y += 0.01f;
        // 플레이어가 설정 화면 바깥으로 나갈 경우 예외 처리
        if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
        if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width;
        if (this->position.y < 240)  this->position.y = 240;
        if (this->position.y + height > WINDOWHEIGHT + 40) {
            this->position.y = WINDOWHEIGHT - height - 100;
            if (!isOnGround) { // 체력 감소가 중복 호출되지 않도록
                takeDamage(1.0f);
                isOnGround = true; // 이미 처리된 상태로 설정
                // 체력 감소에 따라 하트 상태를 즉시 업데이트
                hearts.clear();
                for (int i = 0; i < this->health; i++) {
                    sf::Sprite heartSprite;
                    heartSprite.setTexture(heartTexture);
                    heartSprite.setScale(0.05f, 0.05f); // 하트 크기 조정
                    heartSprite.setPosition(1400.0f + i * 70.0f, 15.0f); // 하트 위치 설정 (x축 간격 조정)
                    hearts.push_back(heartSprite);
                }
            }
        }
        else {
            isOnGround = false; // 공중으로 나가면 다시 초기화
        }
    }

}


void Player::initializeHearts() {
    if (!heartTexture.loadFromFile("heart.png")) {
        std::cerr << "Error loading heart texture!" << std::endl;
        return;
    }
    loadProjectileTextures(); // 텍스처 로드 추가

    // 플레이어 체력만큼 하트를 추가
    changeHeartSprite();
}

void Player::changeHeartSprite() {
    hearts.clear();
    for (int i = 0; i < this->health; i++) {
        sf::Sprite heartSprite;
        heartSprite.setTexture(heartTexture);
        heartSprite.setScale(0.05f, 0.05f); // 하트 크기 조정
        heartSprite.setPosition(1400.0f + i * 70.0f, 15.0f); // 하트 위치 설정 (x축 간격 조정)
        hearts.push_back(heartSprite);

    }
}
void Player::draw(sf::RenderWindow& window) {
    // 하트 스프라이트 그리기
    for (const sf::Sprite& heart : hearts) {

        window.draw(heart);
    }

    if (isBlinking && !isVisible) {
        return; // 깜빡임 상태에서 숨겨진 경우 아무것도 그리지 않음
    }

    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}

void Player::triggerBlink() {
    isBlinking = true;         // 깜빡임 활성화
    isVisible = true;          // 처음엔 보이는 상태
    blinkClock.restart();      // 타이머 초기화
}

void Player::updateBlink() {
    if (isBlinking) {
        float elapsed = blinkClock.getElapsedTime().asSeconds();
        // 깜빡임 종료
        if (elapsed > blinkDuration) {
            isBlinking = false; // 깜빡임 비활성화
            isVisible = true;   // 항상 보이는 상태로 복원
            return;
        }
        // 깜빡이는 간격에 따라 가시성 토글
        if (static_cast<int>(elapsed / blinkInterval) % 2 == 0) {
            isVisible = true;  // 보이는 상태
        }
        else {
            isVisible = false; // 숨겨진 상태
        }
    }
}

void Player::takeDamage(float amount) {
    // 부모 클래스의 takeDamage 호출
    Character::takeDamage(amount);
    // 체력이 감소했을 때 추가 동작 수행
    if (getHealth() > 0) {
        triggerBlink(); // 깜빡임 효과 활성화
    }
}

//방향에 따라서 사진 업로드
void Player::updateDirection(char direction, int stageNumber) {
    if (direction != this->direction) { //버벅거림 막기
        this->direction = direction;
        sf::IntRect textureRect;  // 표시할 텍스처 영역
        if (stageNumber == 2) { // Only change image in stage 3
            if (direction == 'A') {
                textureRect = sf::IntRect(10, 260, 990, 960);
                image("sea_my_unit_left.PNG", textureRect);
                bulletTextures[1].loadFromFile("bullet_left_sea.png");

            }
            else if (direction == 'D') {
                textureRect = sf::IntRect(10, 260, 990, 960);
                image("sea_my_unit_right.PNG", textureRect);
                bulletTextures[1].loadFromFile("bullet_sea.png");

            }
        }
        if (stageNumber == 3) { // Only change image in stage 3
            if (direction == 'A') {
                textureRect = sf::IntRect(0, 0, 990, 710);
                image("land_my_unit_left.PNG", textureRect);
                bulletTextures[2].loadFromFile("bullet_left_land.png");

            }
            else if (direction == 'D') {
                image("land_my_unit_right.PNG", textureRect);
                bulletTextures[2].loadFromFile("bullet_land.png");

            }
        }
        bulletDirection.x *= -1.0f;    // 총알 방향 전환 - 추후 이걸로 가능하도록 변경해야. 
    }

}
void Player::image(std::string textureFile, const sf::IntRect& textureRect) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setTexture(texture);   // 텍스처를 스프라이트에 적용
        // 텍스처 영역이 지정된 경우 해당 영역만 사용
        if (textureRect != sf::IntRect()) {
            sprite.setTextureRect(textureRect);
        }
        sprite.setScale(0.1f, 0.1f);
    }
}

void Player::setPlayer(int stageNumber) {
    std::string textureFile;

    // 기존 공격체 삭제
    bullets.clear();
    missiles.clear();

    allyMissiles.clear(); // 아군 발사체도 삭제
    allyUnits.clear();   // 기존 아군 유닛 삭제 

    this->stageNumber = stageNumber;
        sf::IntRect textureRect;  // 표시할 텍스처 영역
    switch (stageNumber) {
    case 1:
        direction = 'W';
        bulletDirection = sf::Vector2f(0.0f, -1.0f);
        missileDirection = sf::Vector2f(0.0f, -1.0f);
        textureRect = sf::IntRect(5, 0, 995, 850);
        image("sky_my_unit.PNG", textureRect);
        break;
    case 2:
        direction = 'D';
        bulletDirection = sf::Vector2f(1.0f, 0.0f);
        missileDirection = sf::Vector2f(1.0f, 0.0f);
        textureRect = sf::IntRect(10, 260, 990, 960);
        image("sea_my_unit_right.PNG", textureRect);
        break;
    case 3:
        direction = 'D';
        bulletDirection = sf::Vector2f(1.0f, 0.0f);
        missileDirection = sf::Vector2f(0.0f, -1.0f);
        textureRect = sf::IntRect(0, 0, 990, 710);
        image("land_my_unit_right.PNG", textureRect);
        break;
    default:
        direction = 'W';
        break;
    }

    // 공격체 방향 초기화
    //this->bulletDirection = bulletDirection;
    //this->missileDirection = missileDirection;
    bulletDirection = bulletDirection;
    missileDirection = missileDirection;

    
    width = sprite.getTexture()->getSize().x * sprite.getScale().x;
    height = sprite.getTexture()->getSize().y * sprite.getScale().y;
}
void Player::restart() {
    health = 5;
    changeHeartSprite();
    setPlayer(1);
    setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f - width / 2.0f, WINDOWHEIGHT * 4.0f / 5.0f));
    stageNumber = 1;
    killCountNomalUnit = 0;
    killCountEliteUnit1 = 0;
    killCountEliteUnit2 = 0;
    killCountEliteUnit3 = 0;
}

void Player::basicAttack() {

    // 플레이어의 중앙 위치를 계산하여 총알의 시작 위치로 사용
    if (stageNumber == 1) {
        bulletStartPosition = sf::Vector2f(this->position.x + 43, this->position.y);
    }
    if (stageNumber == 2) {
        bulletStartPosition = sf::Vector2f(this->position.x + 50, this->position.y + 30);
        //sf::Vector2f bulletStartPosition(this->position.x + 200, this->position.y+100);
    }
    if (stageNumber == 3) {
        bulletStartPosition = sf::Vector2f(this->position.x + 20, this->position.y + 15);
        //sf::Vector2f bulletStartPosition(this->position.x + 20, this->position.y+20);
    }

    //  bullets.emplace_back(new Bullet(bulletStartPosition, bulletDirection, 10.0f));
      //bullets.push_back(Bullet(bulletStartPosition, bulletDirection, 1.0f));
   
    sf::IntRect textureRect;  // 표시할 텍스처 영역
        // 현재 스테이지에 맞는 텍스처를 발사체에 전달
    Bullet* bullet = new Bullet(bulletStartPosition, bulletDirection, 10.0f);
    bullet->setTexture(bulletTextures[stageNumber - 1], textureRect); // 텍스처 설정
    bullets.emplace_back(bullet);
    //  std::cout << "Bullet created at position: " << bulletStartPosition.x << ", " << bulletStartPosition.y << std::endl;

}

void Player::specialAttack() {
    std::cout << "Nomal Unit 처치 수 : " << killCountNomalUnit << std::endl;
    std::cout << "stage1 Elite Unit 처치 수 : " << killCountEliteUnit1 << std::endl;
    std::cout << "stage2 Elite Unit 처치 수 : " << killCountEliteUnit2 << std::endl;
    std::cout << "stage3 Elite Unit 처치 수 : " << killCountEliteUnit3 << std::endl << std::endl;

    if (canSpecialAttack) {
        // 플레이어의 중앙 위치를 계산하여 미사일의 시작 위치로 사용
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += width / 2.0f; // 플레이어의 중심 x 좌표
        missileStartPosition.y += height / 2.0f; // 플레이어의 중심 y 좌표
        sf::IntRect textureRect;  // 표시할 텍스처 영역
        // 미사일 생성 및 설정
        Missile* missile = new Missile(missileStartPosition, missileDirection, 8.0f);
        missile->isAlly = false;
        missile->setTexture(MissileTextures[stageNumber - 1], textureRect); // 텍스처 설정
        missiles.push_back(missile);

        // 특수 공격 상태 갱신
        timeSinceLastSpecial = 0.0f;  // 쿨타임 초기화
        canSpecialAttack = false;     // 쿨타임 시작
        std::cout << "Special attack activated!" << std::endl;
    }
    else {
        std::cout << "Special attack on cooldown!" << std::endl;
    }

}


void Player::ultimateAttack() {
    if (canUltimateAttack) {
        switch (stageNumber) {
        case 1: // 하늘 스테이지
        {
            std::cout << "Sky ultimate attack activated!" << std::endl;

            // 대기 시간 초기화
            waitTime = 5.0f;  // 하늘 스테이지에서만 5초 대기

            //// 플레이어 위치를 중앙 하단으로 고정
            //this->position = sf::Vector2f(WINDOWWIDTH / 2.0f - width / 2.0f, WINDOWHEIGHT - height);
            //this->sprite.setPosition(this->position);

            // 아군 유닛 텍스처 로드
            if (!allyTexture.loadFromFile("sky_p_unit.PNG")) { /// 이미지 바꿔야 함 
                std::cerr << "Error loading texture for ally units." << std::endl;
                return; // 텍스처를 로드하지 못하면 함수 종료
            }
            float halfWidth = allyTexture.getSize().x * sprite.getScale().x / 2.0f;

            // 아군 유닛 생성 및 초기 위치 설정 (이미지 반절을 뺀 x 값으로 스폰)
            sf::Vector2f leftWingPosition1(600.0f - halfWidth, 900.0f);
            sf::Vector2f leftWingPosition2(750.0f - halfWidth, 900.0f);
            sf::Vector2f rightWingPosition1(1050.0f - halfWidth, 900.0f);
            sf::Vector2f rightWingPosition2(1200.0f - halfWidth, 900.0f);
            std::vector<sf::Vector2f> allyPositions = { leftWingPosition1, leftWingPosition2, rightWingPosition1, rightWingPosition2 };

            // 아군 유닛 생성
            allyUnits.clear(); // 기존 아군 유닛 제거
            for (const auto allyPosition : allyPositions) {
                sf::Sprite allySprite;
                allySprite.setTexture(allyTexture);
                allySprite.setPosition(allyPosition);
                allySprite.setScale(0.1f, 0.1f);
                allyUnits.push_back(allySprite);
            }

            // 필살기 상태 갱신
            timeSinceLastUltimate = 0.0f;  // 쿨타임 초기화
            canUltimateAttack = false;     // 쿨타임 시작
        }
        break;

        case 2: // 바다 스테이지
        {
            //// 땅 스테이지처럼 이동하며(수면 위에서) 기뢰 투하
            //std::cout << "Sea ultimate attack activated!" << std::endl;

            //// 공격기 텍스처 로드
            //if (!allyTexture.loadFromFile("land_p_unit.png")) { // 공격기 이미지 텍스처 로드
            //    std::cerr << "Error loading texture for aircraft units." << std::endl;
            //    return; // 텍스처 로드 실패 시 함수 종료
            //}

            //// 공격기 생성 및 초기 위치 설정 (오른쪽 상단에서 시작)
            //sf::Vector2f aircraftStartPosition(450, 160.0f); // 왼쪽 상단에서 등장
            //sf::Sprite aircraftSprite;
            //aircraftSprite.setTexture(allyTexture);
            //aircraftSprite.setPosition(aircraftStartPosition);
            //aircraftSprite.setScale(0.1f, 0.1f);

            //// 아군 유닛 벡터에 추가
            //allyUnits.clear(); // 기존 아군 유닛 제거
            //allyUnits.push_back(aircraftSprite);

            //// 필살기 상태 갱신
            //timeSinceLastUltimate = 0.0f;  // 쿨타임 초기화
            //canUltimateAttack = false;     // 쿨타임 시작


            // 발사체 하나 중앙에서 폭발
            std::cout << "Sea ultimate attack activated!" << std::endl;

            // 발사체 초기값 설정
            sf::Vector2f missileStartPosition(400, 600); // 왼쪽 끝에서 시작
            sf::Vector2f missileDirection(1.0f, 0.0f); // 오른쪽으로 직선 이동
            float missileSpeed = 3.0f;  // 발사 속도 (바다 스테이지)
            Missile* missile = new Missile(missileStartPosition, missileDirection, missileSpeed);
            missile->isAlly = true;
            sf::IntRect textureRect;
            missile->setTexture(AllMissileTextures[stageNumber - 1], textureRect);
            // 설정된 방향과 속도로 발사체 생성
            allyMissiles.emplace_back(missile);


            // 필살기 상태 갱신
            timeSinceLastUltimate = 0.0f;  // 쿨타임 초기화 
            canUltimateAttack = false;     // 쿨타임 시작
        }
        break;

        case 3: // 땅 스테이지
        {
            std::cout << "Land ultimate attack activated!" << std::endl;

            // 공격기 텍스처 로드
            if (!allyTexture.loadFromFile("land_p_unit.png")) { // 공격기 이미지 텍스처 로드
                std::cerr << "Error loading texture for aircraft units." << std::endl;
                return; // 텍스처 로드 실패 시 함수 종료
            }

            // 공격기 생성 및 초기 위치 설정 (오른쪽 상단에서 시작)
            sf::Vector2f aircraftStartPosition(WINDOWWIDTH - 450, 50.0f); // 오른쪽 상단에서 등장
            sf::Sprite aircraftSprite;
            aircraftSprite.setTexture(allyTexture);
            aircraftSprite.setPosition(aircraftStartPosition);
            aircraftSprite.setScale(0.2f, 0.2f);

            // 아군 유닛 벡터에 추가
            allyUnits.clear(); // 기존 아군 유닛 제거
            allyUnits.push_back(aircraftSprite);

            // 필살기 상태 갱신
            timeSinceLastUltimate = 0.0f;  // 쿨타임 초기화
            canUltimateAttack = false;     // 쿨타임 시작
        }
        break;

        default:
            std::cout << "Invalid stage number for ultimate attack!" << std::endl;
            break;
        }
    }
    else {
        std::cout << "Ultimate attack on cooldown!" << std::endl;
    }
}

void Player::allyAttack() {
    for (const auto& ally : allyUnits) {
        sf::Vector2f missileStartPosition = ally.getPosition();
        sf::Vector2f missileDirection;
        float missileSpeed, missileRange, missileDamage;
        sf::Texture missileTexture; // 텍스처 로드용 변수
       

        if (stageNumber == 1) {  // 하늘 스테이지에서 발사체 위쪽으로 발사
            
            sf::Sprite allMiSprite;
            missileStartPosition.x += ally.getGlobalBounds().width / 2.0f;  // 아군 유닛의 중앙 위치에서 발사
            missileStartPosition.y -= 10.0f;  // 약간 위쪽에서 발사
            missileDirection = sf::Vector2f(0.0f, -1.0f);  // 위쪽 방향
            missileSpeed = 5.0f;    // 발사 속도 (하늘 스테이지)
            missileRange = 100.0f;   // 미사일 충돌 범위
            missileDamage = 25.0f;  // 미사일 공격력
            //image = AllMissileTextures[0].copyToImage(); // 하늘 스테이지용 이미지 복사
            //missile->setTexture(AllMissileTextures[0], textureRect);
        }
        //else if (stageNumber == 2) {  // 바다 스테이지에서 발사체 오른쪽으로 발사
        //    sf::Vector2f missileStartPosition(450, 600); // 왼쪽 끝에서 시작
        //    sf::Vector2f missileDirection(1.0f, 0.0f); // 오른쪽으로 발사
        //    float missileSpeed = 3.0f;  // 발사 속도 (바다 스테이지)
        //}
        else if (stageNumber == 3) {  // 땅 스테이지에서 발사체 아래쪽으로 발사
            missileStartPosition.x += ally.getGlobalBounds().width / 2.0f;  // 아군 유닛의 중앙 위치에서 발사
            missileStartPosition.y += ally.getGlobalBounds().height + 30.0f;  // 약간 아래쪽에서 발사
            missileDirection = sf::Vector2f(0.0f, 1.0f);  // 아래쪽 방향
            missileSpeed = 3.0f;  // 발사 속도 (땅 스테이지)
            missileRange = 200.0f;   // 미사일 충돌 범위
            missileDamage = 300.0f;  // 미사일 공격력
            //image = AllMissileTextures[2].copyToImage();; // 땅 스테이지용 이미지 복사
            //missile->setTexture(AllMissileTextures[2], textureRect);
        }
       
        //missileTexture.loadFromImage(image);

        // 설정된 방향과 속도로 발사체 생성
        Missile* missile = new Missile(missileStartPosition, missileDirection, missileSpeed);
        sf::IntRect textureRect;  // 표시할 텍스처 영역
        missile->setTexture(AllMissileTextures[stageNumber - 1], textureRect);

        missile->isAlly = true;  // 아군 미사일로 설정
        missile->changeRange(missileRange);
        missile->changeDamage(missileDamage);

        allyMissiles.emplace_back(missile);
        //std::cout << "Texture size: " << AllMissileTextures[0].getSize().x << ", " << AllMissileTextures[0].getSize().y << std::endl;
        //std::cout << "Sprite bounds: " << missile->sprite.getGlobalBounds().left << ", " << missile->sprite.getGlobalBounds().top << std::endl;

    }
}

void Player::drawAllies(sf::RenderWindow& window) {
    for (auto& ally : allyUnits) {
        window.draw(ally);
    }
}


void Player::updateCooldowns(float dt) {
    // 특수 공격 쿨타임 업데이트
    if (!canSpecialAttack) {
        timeSinceLastSpecial += dt; // 프레임 간 경과 시간을 누적
        if (timeSinceLastSpecial >= specialAttackCooldown) {
            canSpecialAttack = true; // 쿨타임 종료 시 특수 공격 가능하게 설정
            std::cout << "Special attack is ready!" << std::endl;
        }
    }

    // 필살기 쿨타임 업데이트
    if (!canUltimateAttack) {
        timeSinceLastUltimate += dt; // 프레임 간 경과 시간을 누적
        if (timeSinceLastUltimate >= ultimateAttackCooldown) {
            canUltimateAttack = true; // 쿨타임 종료 시 필살기 가능하게 설정
            std::cout << "Ultimate attack is ready!" << std::endl;
        }
    }
}

void Player::updateAllies(float dt, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Missile>>& globalMissiles) {
    switch (stageNumber) {
    case 1: // 하늘 스테이지
        // 하늘 스테이지에서 아군 유닛 위쪽으로 느리게 이동
        //for (auto& ally : allyUnits) {
        //    sf::Vector2f position = ally.getPosition();
        //    position.y -= 100.0f * dt; // 위쪽으로 이동 (속도 50.0f * delta time)
        //    ally.setPosition(position);
        //}

        //// 화면 밖으로 나간 아군 유닛 제거
        //allyUnits.erase(
        //    std::remove_if(allyUnits.begin(), allyUnits.end(),
        //        [](sf::Sprite& ally) {
        //            return ally.getPosition().y + ally.getGlobalBounds().height < 0; // 화면 위쪽 밖으로 나간 경우
        //        }),
        //    allyUnits.end()
        //);
        // 하늘 스테이지에서 5초 동안 제자리에 있다가  대각선으로 이동

    {
        // 대기 시간 체크
        if (waitTime > 0.0f) {
            waitTime -= dt;

            // Y축 이동
            for (auto& ally : allyUnits) {
                sf::Vector2f position = ally.getPosition();
                position.y -= 100.0f * dt; // 천천히 위쪽으로 이동
                if (position.y < 700.0f) { // 지정된 위치까지 이동
                    position.y = 700.0f;
                }
                ally.setPosition(position);
            }
            return;  // 대기 시간이 지나기 전까지는 대각선 이동 안 함
        }

        // 하늘 스테이지에서 아군 유닛 대각선 위쪽으로 이동
        for (size_t i = 0; i < allyUnits.size(); ++i) {
            sf::Vector2f position = allyUnits[i].getPosition();
            if (i < allyUnits.size() / 2) {
                position.x -= 100.0f * dt; // 왼쪽 위 대각선으로 이동
                position.y -= 50.0f * dt;
            }
            else {
                position.x += 100.0f * dt; // 오른쪽 위 대각선으로 이동
                position.y -= 50.0f * dt;
            }
            allyUnits[i].setPosition(position);
        }

        allyUnits.erase(
            std::remove_if(allyUnits.begin(), allyUnits.end(),
                [](sf::Sprite& ally) {
                    return ally.getPosition().y < -50 || // 화면 위쪽을 벗어난 경우
                        ally.getPosition().x < -50 || // 화면 왼쪽을 벗어난 경우
                        ally.getPosition().x > WINDOWWIDTH + 50 || // 화면 오른쪽을 벗어난 경우
                        ally.getPosition().y > WINDOWHEIGHT + 50; // 화면 아래쪽을 벗어난 경우
                }),
            allyUnits.end()
        );

    }
    break;

    case 2: // 바다 스테이지
        //// 바다 스테이지에서 아군 유닛은 왼쪽에서 오른쪽으로 이동
        //for (auto& ally : allyUnits) {
        //    sf::Vector2f position = ally.getPosition();
        //    position.x += 100.0f * dt; // 오른쪽으로 이동 (속도 100.0f * delta time)
        //    ally.setPosition(position);
        //}

        //// 화면 밖으로 나간 아군 유닛 제거
        //allyUnits.erase(
        //    std::remove_if(allyUnits.begin(), allyUnits.end(),
        //        [](sf::Sprite& ally) {
        //            return ally.getPosition().x > WINDOWWIDTH; // 화면 오른쪽 밖으로 나간 경우
        //        }),
        //    allyUnits.end()
        //);

         // 필살기 중앙에 도달하면 적군 전체 제거
        if (std::any_of(allyMissiles.begin(), allyMissiles.end(), [](Missile* missile) {
            return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
            })) {
            // 적군 전체 삭제
            for (auto* enemy : enemies) {
                if (dynamic_cast<NormalUnit*>(enemy) == enemy) killCountNomalUnit++;
                else if (dynamic_cast<EliteUnit*>(enemy) == enemy) this->countKillElite();
                delete enemy;  // 동적 메모리 해제
            }
            enemies.clear(); // 적군 벡터 초기화
            for (auto& enemyMissile : globalMissiles) {
                //delete enemyMissile;  // 동적 메모리 해제
            }
            globalMissiles.clear(); // 적군 공격체 벡터 초기화
        }

        allyMissiles.erase(
            std::remove_if(allyMissiles.begin(), allyMissiles.end(),
                [](Missile* missile) {
                    return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
                }),
            allyMissiles.end()

        );
    
            break;

    case 3: // 땅 스테이지
        for (auto& ally : allyUnits) {
            sf::Vector2f position = ally.getPosition();
            position.x -= 50.0f * dt; // 왼쪽으로 이동 (속도 50.0f * delta time)
            ally.setPosition(position);
        }

        // 화면 밖으로 나간 아군 유닛 제거
        allyUnits.erase(
            std::remove_if(allyUnits.begin(), allyUnits.end(),
                [](sf::Sprite& ally) {
                    return ally.getPosition().x > WINDOWWIDTH; // 화면 오른쪽 밖으로 나간 경우
                }),
            allyUnits.end()
        );
        break;

    default:
        break;
    }
}

void Player::collision(std::vector<Enemy*>& enemies) {
    // 플레이어의 공격과 적군의 충돌 처리
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); enemyIt++) {
        bool enemyDestroyed = false;

        if (*enemyIt == nullptr) {  // nullptr 체크
            return;
        }

        // Missile 처리   // 미사일의 개수가 총알에 비해 비교적 적고 범위 공격을 인해 continue가 자주 발생할 수 있어 총알보다 우선 충돌처리
        for (auto missileIt = missiles.begin(); missileIt != missiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr 체크
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);

                for (auto enemyTmpIt = enemies.begin(); enemyTmpIt != enemies.end(); enemyTmpIt++) {
                    if (*enemyTmpIt == nullptr) {  // nullptr 체크
                        break;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                    if (distance < (*missileIt)->getRange()) {

                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy의 체력 감소

                        if ((*enemyTmpIt)->getHealth() <= 0) {
                            //if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                           // else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                            enemyDestroyed = true;
                        }
                    }

                }
                (*missileIt)->crashed();    // 미사일 충돌 됨으로 상태 수정
                
            }
        }
        if (enemyDestroyed) {
            continue; // Enemy가 삭제되었으므로 다음 Enemy로 이동
        }


        
        // Bullet 처리
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++) {
            if ((*bulletIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시

                /*std::cout << "Bullet Global Bounds: " << (*bulletIt)->shape.getGlobalBounds().left << ", "
                    << (*bulletIt)->shape.getGlobalBounds().top << ", "
                    << (*bulletIt)->shape.getGlobalBounds().width << ", "
                    << (*bulletIt)->shape.getGlobalBounds().height << std::endl;

                std::cout << "Enemy Global Bounds: " << (*enemyIt)->sprite.getGlobalBounds().left << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().top << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().width << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().height << std::endl;*/

                float damage = (*bulletIt)->getDamage();
                if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) damage /= 10;

                (*enemyIt)->takeDamage(damage);   // Enemy의 체력 감소
                (*bulletIt)->crashed();
                if ((*enemyIt)->getHealth() <= 0) {
                    //if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                    //else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                    break;
                }
            }
        }

        // 필살기 Missile 처리   
        if (stageNumber != 2) {
            for (auto missileIt = allyMissiles.begin(); missileIt != allyMissiles.end(); missileIt++) {
                if (*missileIt == nullptr) {  // nullptr 체크
                    break;
                }
                if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시
                    sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                    sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                    //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);

                    for (auto enemyTmpIt = enemies.begin(); enemyTmpIt != enemies.end(); enemyTmpIt++) {
                        if (*enemyTmpIt == nullptr) {  // nullptr 체크
                            break;
                        }
                        sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                        sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                        sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                        double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                        if (distance < (*missileIt)->getRange()) {

                            (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy의 체력 감소

                            // 이 이후에 충돌처리 할 것이 없으므로 적군이 파괴 되었는지 여부는 알 필요 없음
                            /*if ((*enemyTmpIt)->getHealth() <= 0) {
                                if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                                else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                            }*/
                        }

                    }
                    (*missileIt)->crashed();    // 미사일 충돌 됨으로 상태 수정

                }
            }
        }


    }

    deleteThisProjectile();

}

void Player::healUnitCollision(std::vector<HealUnit*> healUnits) {
    // 플레이어의 공격과 적군의 충돌 처리
    for (auto enemyIt = healUnits.begin(); enemyIt != healUnits.end(); enemyIt++) {
        bool enemyDestroyed = false;
        if (*enemyIt == nullptr) {  // nullptr 체크
            return;
        }
        // Missile 처리   // 미사일의 개수가 총알에 비해 비교적 적고 범위 공격을 인해 continue가 자주 발생할 수 있어 총알보다 우선 충돌처리
        for (auto missileIt = missiles.begin(); missileIt != missiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr 체크
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);
                for (auto enemyTmpIt = healUnits.begin(); enemyTmpIt != healUnits.end(); enemyTmpIt++) {
                    if (*enemyTmpIt == nullptr) {  // nullptr 체크
                        break;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);
                    if (distance < (*missileIt)->getRange()) {
                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy의 체력 감소
                        if ((*enemyTmpIt)->getHealth() <= 0) {
                            //if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                           // else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                            enemyDestroyed = true;
                        }
                    }
                }
                (*missileIt)->crashed();    // 미사일 충돌 됨으로 상태 수정
            }
        }
        if (enemyDestroyed) {
            continue; // Enemy가 삭제되었으므로 다음 Enemy로 이동
        }
        // 필살기 Missile 처리   
        for (auto missileIt = allyMissiles.begin(); missileIt != allyMissiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr 체크
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);
                for (auto enemyTmpIt = healUnits.begin(); enemyTmpIt != healUnits.end(); enemyTmpIt++) {
                    if (*enemyTmpIt == nullptr) {  // nullptr 체크
                        break;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);
                    if (distance < (*missileIt)->getRange()) {
                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy의 체력 감소
                    }
                }
                (*missileIt)->crashed();    // 미사일 충돌 됨으로 상태 수정
            }
        }

    }
    deleteThisProjectile();
}


void Player::enemyProjectileCollision(std::vector<std::unique_ptr<Missile>>& globalMissiles) {   // 적군 공격체-플레이어 충돌 처리
   
    for (auto enemyMissileIt = globalMissiles.begin(); enemyMissileIt != globalMissiles.end(); enemyMissileIt++) {
        if ((*enemyMissileIt)->checkCrashed()) continue;        // 이미 충돌이 일어났다면 continue
        bool misileDestroyed = false;
        if (*enemyMissileIt == nullptr) {  // nullptr 체크
            break;
        }

        // 플레이어 Missile 처리   
        // 미사일의 개수가 총알에 비해 비교적 적고 범위 공격을 인해 continue가 자주 발생할 수 있어 총알보다 우선 충돌처리
        for (auto missileIt = missiles.begin(); missileIt != missiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr 체크
                break;
            }
            if ((*enemyMissileIt)->sprite.getGlobalBounds().intersects((*missileIt)->sprite.getGlobalBounds())) { // 충돌 발생 시 
                misileDestroyed = true;
                (*missileIt)->crashed();    // 플레이어 미사일 충돌 됨으로 상태 수정
                sf::Vector2f playerMissilePostion = (*missileIt)->getPosition();

                for (auto enemyMissilTmpIt = globalMissiles.begin(); enemyMissilTmpIt != globalMissiles.end(); enemyMissilTmpIt++) {    // 범위 내 적군 미사일 재검사
                    sf::Vector2f enemyMissilePostion = (*enemyMissilTmpIt)->getPosition();
                    sf::Vector2f dist = playerMissilePostion - enemyMissilePostion;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                    /* std::cout << "player 미사일 x,y : " << playerMissilePostion.x << " " << playerMissilePostion.y << std::endl;
                    std::cout << "enemy 미사일 x,y : " << enemyMissilePostion.x << " " << enemyMissilePostion.y << std::endl;
                    std::cout << "미사일 distance : " << distance << std::endl;*/
                    if (distance < (*missileIt)->getRange()) {
                        (*enemyMissilTmpIt)->crashed();    // 적군 미사일 충돌 됨으로 상태 수정
                    }
                }
            }
            if (misileDestroyed) break;
        }

        if (misileDestroyed) {
            continue; // Enemy가 삭제되었으므로 다음 Enemy로 이동
        }

        // 필살기 Missile 처리   
        if (stageNumber != 2) {     // 바다 스테이지가 아닌 경우
            for (auto missileIt = allyMissiles.begin(); missileIt != allyMissiles.end(); missileIt++) {
                if (*missileIt == nullptr) {  // nullptr 체크
                    break;
                }
                if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyMissileIt)->sprite.getGlobalBounds())) { // 충돌 발생 시
                    // sf::FloatRect boundsMissile = (*missileIt)->shape.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                    //sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                    ////sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);

                    (*enemyMissileIt)->crashed();    // 미사일 충돌 됨으로 상태 수정
                    (*missileIt)->crashed();    // 미사일 충돌 됨으로 상태 수정
                    misileDestroyed = true;
                }
            }
            if (misileDestroyed) {
                continue; // Enemy가 삭제되었으므로 다음 Enemy로 이동
            }
        }

        // 플레이어와 충돌 처리
        if ((*enemyMissileIt)->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds())) { // 충돌 발생 시
            this->takeDamage(1.0f);
            this->changeHeartSprite();
            (*enemyMissileIt)->crashed();    // 미사일 충돌 됨으로 상태 수정
        }
    }
    deleteThisProjectile();

}

void Player::deleteThisProjectile() {
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](Bullet* bullet) {
                return bullet->checkCrashed();
            }),
        bullets.end()
    );

    missiles.erase(
        std::remove_if(missiles.begin(), missiles.end(),
            [](Missile* missile) {
                return missile->checkCrashed();
            }),
        missiles.end()
    );

    allyMissiles.erase(
        std::remove_if(allyMissiles.begin(), allyMissiles.end(),
            [](Missile* Missile) {
                return Missile->checkCrashed();
            }),
        allyMissiles.end()
    );
}

void Player::countKillElite() {
    switch (stageNumber) {
    case 1:
        this->killCountEliteUnit1++;
        break;
    case 2:
        this->killCountEliteUnit2++;
        break;
    case 3:
        this->killCountEliteUnit3++;
        break;
    default:
        break;
    }
}

void Player::updateAttack() {

    // 총알과 미사일의 상태 업데이트
    for (Bullet* bullet : bullets) {
        bullet->update(); // 발사체 상태 업데이트
    }
    for (Missile* missile : missiles) {
        missile->update(); // 발사체 상태 업데이트
    }

    // 아군 유닛의 발사체 업데이트
    for (Missile* allyMissile : allyMissiles) {
      /*  std::cout << allyMissile->sprite.getGlobalBounds().left << " " << allyMissile->sprite.getGlobalBounds().top << " "
            << allyMissile->sprite.getGlobalBounds().width << " " << allyMissile->sprite.getGlobalBounds().height << " " << std::endl;*/
        allyMissile->update();
    }

    //if (stageNumber == 2) {
    //    // 필살기 중앙에서 도달하면 적군 전체 제거
    //    if (std::any_of(allyMissiles.begin(), allyMissiles.end(), [](Missile* missile) {
    //        return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
    //        })) {
    //        // 적군 전체 삭제
    //        for (auto* enemy : enemies) {
    //            delete enemy;  // 동적 메모리 해제
    //        }
    //        enemies.clear(); // 적군 벡터 초기화
    //    }

    //    allyMissiles.erase(
    //        std::remove_if(allyMissiles.begin(), allyMissiles.end(),
    //            [](Missile* missile) {
    //                return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
    //            }),
    //        allyMissiles.end()

    //    );
    //    
    //}

    // 화면 밖으로 나간 발사체 제거
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](Bullet* bullet) {
                return bullet->isOffScreen();
            }),
        bullets.end()
    );

    missiles.erase(
        std::remove_if(missiles.begin(), missiles.end(),
            [](Missile* missile) {
                return missile->isOffScreen();
            }),
        missiles.end()
    );

    allyMissiles.erase(
        std::remove_if(allyMissiles.begin(), allyMissiles.end(),
            [](Missile* Missile) {
                return Missile->isOffScreen();
            }),
        allyMissiles.end()
    );
}


void Player::renderAttack(sf::RenderWindow& window) {
    for (Bullet* bullet : bullets) {
        bullet->draw(window); // 발사체 상태 업데이트
        //  std::cout << "Drawing bullet at position: " << bullet->position.x << ", " << bullet->position.y << std::endl;

    }
    for (Missile* missile : missiles) {
        missile->draw(window); // 발사체 상태 업데이트
    }

    // 아군 유닛의 발사체 그리기
    for (Missile* Missile : allyMissiles) {
        Missile->draw(window);
    }
}
float Player::getUltimateAttackRemainingCooldown() const {
    if (canUltimateAttack) {
        return 0.0f;
    }
    else {
        float remaining = ultimateAttackCooldown - timeSinceLastUltimate;
        return remaining > 0.0f ? remaining : 0.0f;
    }
}
float Player::getSpecialAttackRemainingCooldown() const {
    if (canSpecialAttack) {
        return 0.0f;
    }
    else {
        float remaining = specialAttackCooldown - timeSinceLastSpecial;
        return remaining > 0.0f ? remaining : 0.0f;
    }
}


void Player::loadProjectileTextures() {

    if (!bulletTextures[0].loadFromFile("bullet_sky.png")) {
        std::cerr << "Error loading bullet_sky.png!" << std::endl;
    }
    if (!bulletTextures[1].loadFromFile("bullet_sea.png")) {
        std::cerr << "Error loading bullet_sea.png!" << std::endl;
    }
    if (!bulletTextures[2].loadFromFile("bullet_land.png")) {
        std::cerr << "Error loading bullet_land.png!" << std::endl;
    }
    if (!MissileTextures[0].loadFromFile("missile_sky.png")) {
        std::cerr << "Error loading bullet_sky.png!" << std::endl;
    }
    if (!MissileTextures[1].loadFromFile("missile_sea.png")) {
        std::cerr << "Error loading bullet_sea.png!" << std::endl;
    }
    if (!MissileTextures[2].loadFromFile("missile_land.png")) {
        std::cerr << "Error loading bullet_land.png!" << std::endl;
    }
    if (!AllMissileTextures[0].loadFromFile("bullet_sky.png")) {
        std::cerr << "Error loading sky_missile.png!" << std::endl;
    }
    if (!AllMissileTextures[1].loadFromFile("E_sea.png")) {
        std::cerr << "Error loading E_sea.png!" << std::endl;
    }
    if (!AllMissileTextures[2].loadFromFile("E_land.png")) {
        std::cerr << "Error loading land_missile.png!" << std::endl;
    }
}