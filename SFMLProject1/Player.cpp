#include "Player.h"
#include "Bullet.h" 
#include <iostream>  

extern int WINDOWWIDTH, WINDOWHEIGHT;
// health,  speed, sf::Vector2f position
Player::Player() : Character(5, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f - width / 2.0f, WINDOWHEIGHT * 4.0f / 5.0f)) {
    //missileLaunched = false; 

    // 특수 공격 관련 변수 초기화
    specialAttackCooldown = 1.0f; // 특수 공격 쿨타임: 5초
    timeSinceLastSpecial = specialAttackCooldown; // 게임 시작 시 바로 사용할 수 있도록 설정
    canSpecialAttack = true;

    // 필살기 관련 변수 초기화
    ultimateAttackCooldown = 1.0f; // 필살기 쿨타임 20초
    canUltimateAttack = false;

    waitTime = 0.0f; // 초기화

    initializeHearts();
}



void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // 위치 업데이트

    // 플레이어가 설정 화면 바깥으로 나갈 경우 예외 처리
    if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
    if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width;
    if (this->position.y < 0)  this->position.y = 0;
    if (this->position.y + height > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - height;

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
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
    // 하트 스프라이트 그리기
    for (const sf::Sprite& heart : hearts) {

        window.draw(heart);
    }
}

//방향에 따라서 사진 업로드
void Player::updateDirection(char direction, int stageNumber) {
    if (direction != this->direction) { //버벅거림 막기
        this->direction = direction;
        if (stageNumber == 2) { // Only change image in stage 3
            if (direction == 'A') {
                image("sea_my_unit_left.png");
                bulletTextures[1].loadFromFile("bullet_left_sea.png");

            }
            else if (direction == 'D') {
                image("sea_my_unit_right.png");
                bulletTextures[1].loadFromFile("bullet_sea.png");

            }
        }
        if (stageNumber == 3) { // Only change image in stage 3
            if (direction == 'A') {
                image("land_my_unit_left.png");
                bulletTextures[2].loadFromFile("bullet_left_land.png");

            }
            else if (direction == 'D') {
                image("land_my_unit_right.png");
                bulletTextures[2].loadFromFile("bullet_land.png");

            }
        }
        bulletDirection.x *= -1.0f;    // 총알 방향 전환 - 추후 이걸로 가능하도록 변경해야. 
    }

}
void Player::image(std::string textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setScale(0.1f, 0.1f);
        sprite.setTexture(texture);
        sprite.setPosition(position);
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


    switch (stageNumber) {
    case 1:
        direction = 'W';
        bulletDirection = sf::Vector2f(0.0f, -1.0f);
        missileDirection = sf::Vector2f(0.0f, -1.0f);
        textureFile = "sky_my_unit.PNG";
        break;
    case 2:
        direction = 'D';
        bulletDirection = sf::Vector2f(1.0f, 0.0f);
        missileDirection = sf::Vector2f(1.0f, 0.0f);
        textureFile = "sea_my_unit_right.png";
        break;
    case 3:
        direction = 'D';
        bulletDirection = sf::Vector2f(1.0f, 0.0f);
        missileDirection = sf::Vector2f(0.0f, -1.0f);
        textureFile = "land_my_unit_right.PNG";
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

    // 플레이어 이미지 처리
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setScale(0.1f, 0.1f);
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }
    width = sprite.getTexture()->getSize().x * sprite.getScale().x;
    height = sprite.getTexture()->getSize().y * sprite.getScale().y;
}


void Player::basicAttack() {

    // 플레이어의 중앙 위치를 계산하여 총알의 시작 위치로 사용
    sf::Vector2f bulletStartPosition = this->position;

    //  bullets.emplace_back(new Bullet(bulletStartPosition, bulletDirection, 10.0f));
      //bullets.push_back(Bullet(bulletStartPosition, bulletDirection, 1.0f));

        // 현재 스테이지에 맞는 텍스처를 발사체에 전달
    Bullet* bullet = new Bullet(bulletStartPosition, bulletDirection, 10.0f);
    bullet->setTexture(bulletTextures[stageNumber - 1]); // 텍스처 설정
    bullets.emplace_back(bullet);
    //  std::cout << "Bullet created at position: " << bulletStartPosition.x << ", " << bulletStartPosition.y << std::endl;

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
}



void Player::specialAttack() {

    if (canSpecialAttack) {
        // 플레이어의 중앙 위치를 계산하여 미사일의 시작 위치로 사용
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += width / 2.0f; // 플레이어의 중심 x 좌표
        missileStartPosition.y += height / 2.0f; // 플레이어의 중심 y 좌표

        // 미사일 생성 및 설정
        Missile* missile = new Missile(missileStartPosition, missileDirection, 8.0f);
        missile->isAlly = false;
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
            if (!allyTexture.loadFromFile("sky_my_unit.PNG")) { /// 이미지 바꿔야 함 
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
            // 땅 스테이지처럼 이동하며(수면 위에서) 기뢰 투하
            //std::cout << "Sea ultimate attack activated!" << std::endl;

            //// 공격기 텍스처 로드
            //if (!allyTexture.loadFromFile("sea_my_unit_right.png")) { // 공격기 이미지 텍스처 로드
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

            // 발사체 생성
            sf::Vector2f missileStartPosition(400, 600); // 왼쪽 끝에서 시작
            sf::Vector2f missileDirection(1.0f, 0.0f); // 오른쪽으로 직선 이동
            float missileSpeed = 3.0f;  // 발사 속도 (바다 스테이지)

            // 설정된 방향과 속도로 발사체 생성
            allyMissiles.emplace_back(new Missile(missileStartPosition, missileDirection, missileSpeed));


            // 필살기 상태 갱신
            timeSinceLastUltimate = 0.0f;  // 쿨타임 초기화 
            canUltimateAttack = false;     // 쿨타임 시작
        }
        break;

        case 3: // 땅 스테이지
        {
            std::cout << "Land ultimate attack activated!" << std::endl;

            // 공격기 텍스처 로드
            if (!allyTexture.loadFromFile("land_elite_unit_left.png")) { // 공격기 이미지 텍스처 로드
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
        float missileSpeed;

        if (stageNumber == 1) {  // 하늘 스테이지에서 발사체 위쪽으로 발사
            missileStartPosition.x += ally.getGlobalBounds().width / 2.0f;  // 아군 유닛의 중앙 위치에서 발사
            missileStartPosition.y -= 10.0f;  // 약간 위쪽에서 발사
            missileDirection = sf::Vector2f(0.0f, -1.0f);  // 위쪽 방향
            missileSpeed = 5.0f;  // 발사 속도 (하늘 스테이지)
        }
        //else if (stageNumber == 2) {  // 바다 스테이지에서 발사체 오른쪽으로 발사
        //    sf::Vector2f missileStartPosition(450, 600); // 왼쪽 끝에서 시작
        //    sf::Vector2f missileDirection(1.0f, 0.0f); // 오른쪽으로 발사
        //    float missileSpeed = 3.0f;  // 발사 속도 (바다 스테이지)
        //}
        else if (stageNumber == 3) {  // 땅 스테이지에서 발사체 아래쪽으로 발사
            missileStartPosition.x += ally.getGlobalBounds().width / 2.0f;  // 아군 유닛의 중앙 위치에서 발사
            missileStartPosition.y += ally.getGlobalBounds().height - 120.0f;  // 약간 아래쪽에서 발사
            missileDirection = sf::Vector2f(0.0f, 1.0f);  // 아래쪽 방향
            missileSpeed = 3.0f;  // 발사 속도 (땅 스테이지)
        }

        // 설정된 방향과 속도로 발사체 생성
        Missile* missile = new Missile(missileStartPosition, missileDirection, missileSpeed);
        missile->isAlly = true;  // 아군 미사일로 설정

        allyMissiles.push_back(missile);
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

void Player::updateAllies(float dt) {
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

    //case 2: // 바다 스테이지
    //    // 바다 스테이지에서 아군 유닛은 왼쪽에서 오른쪽으로 이동
    //    for (auto& ally : allyUnits) {
    //        sf::Vector2f position = ally.getPosition();
    //        position.x += 100.0f * dt; // 오른쪽으로 이동 (속도 100.0f * delta time)
    //        ally.setPosition(position);
    //    }

    //    // 화면 밖으로 나간 아군 유닛 제거
    //    allyUnits.erase(
    //        std::remove_if(allyUnits.begin(), allyUnits.end(),
    //            [](sf::Sprite& ally) {
    //                return ally.getPosition().x > WINDOWWIDTH; // 화면 오른쪽 밖으로 나간 경우
    //            }),
    //        allyUnits.end()
    //    );
    //    break;

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
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
        bool enemyDestroyed = false;

        if (*enemyIt == nullptr) {  // nullptr 체크
            enemyIt = enemies.erase(enemyIt);
            continue;
        }

        // Missile 처리   // 미사일의 개수가 총알에 비해 비교적 적고 범위 공격을 인해 continue가 자주 발생할 수 있어 총알보다 우선 충돌처리
        for (auto missileIt = missiles.begin(); missileIt != missiles.end();) {
            if (*missileIt == nullptr) {  // nullptr 체크
                missileIt = missiles.erase(missileIt);
                continue;
            }
            if ((*missileIt)->shape.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시
                sf::FloatRect boundsMissile = (*missileIt)->shape.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);

                for (auto enemyTmpIt = enemies.begin(); enemyTmpIt != enemies.end(); ) {
                    if (*enemyTmpIt == nullptr) {  // nullptr 체크
                        enemyTmpIt = enemies.erase(enemyTmpIt);
                        continue;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                    if (distance < (*missileIt)->getRange()) {

                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy의 체력 감소



                        if ((*enemyTmpIt)->getHealth() <= 0) {
                            delete* enemyTmpIt;                                // 동적 메모리 해제
                            enemyTmpIt = enemies.erase(enemyTmpIt);            // Enemy 삭제

                            enemyDestroyed = true;
                        }
                    }
                    else enemyTmpIt++;

                }
                delete* missileIt;                                     // 동적 메모리 해제
                missileIt = missiles.erase(missileIt);                 // Bullet 삭제 후 다음 요소를 가리킴
                /////////
                return;  // enemy가 수정되면 가장 바깥 for문에서 에러가 발생하는 듯해서 그냥 미사일 범위 처리 되면 업데이트는 종료            
                ////////
            }
            else {                                                  // 충돌이 발생하지 않은 경우 미사일 업데이트
                // 매우 중요
                // (*missileIt)->update(); // Missile 상태를 충돌 처리 내부에서 업데이트 할 경우 적군이 없을 경우 업데이트가 되지 않을 수 있다
                ++missileIt;
            }
        }
        if (enemyDestroyed) {
            continue; // Enemy가 삭제되었으므로 다음 Enemy로 이동
        }

        if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) {
            // Bullet 처리
            for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {

                if ((*bulletIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시

                    /*std::cout << "Bullet Global Bounds: " << (*bulletIt)->shape.getGlobalBounds().left << ", "
                        << (*bulletIt)->shape.getGlobalBounds().top << ", "
                        << (*bulletIt)->shape.getGlobalBounds().width << ", "
                        << (*bulletIt)->shape.getGlobalBounds().height << std::endl;

                    std::cout << "Enemy Global Bounds: " << (*enemyIt)->sprite.getGlobalBounds().left << ", "
                        << (*enemyIt)->sprite.getGlobalBounds().top << ", "
                        << (*enemyIt)->sprite.getGlobalBounds().width << ", "
                        << (*enemyIt)->sprite.getGlobalBounds().height << std::endl;*/

                    (*enemyIt)->takeDamage((*bulletIt)->getDamage());   // Enemy의 체력 감소
                    delete* bulletIt;                                   // 동적 메모리 해제
                    bulletIt = bullets.erase(bulletIt);                 // Bullet 삭제 후 다음 요소를 가리킴

                    if ((*enemyIt)->getHealth() <= 0) {
                        delete* enemyIt;                                // 동적 메모리 해제
                        enemyIt = enemies.erase(enemyIt);               // Enemy 삭제

                        enemyDestroyed = true;
                        break;                                          // Enemy가 삭제되었으므로 현재 Enemy와 더 이상의 충돌 검사 불필요
                    }
                }
                else {                                                  // 충돌이 발생하지 않은 경우 총알 업데이트
                    // 매우 중요
                    // (*bulletIt)->update(); // Bullet 상태를 충돌 처리 내부에서 업데이트 할 경우 적군이 없을 경우 업데이트가 되지 않을 수 있다
                    ++bulletIt;
                }
            }
            if (enemyDestroyed) {
                continue; // Enemy가 삭제되었으므로 다음 Enemy로 이동
            }
        }

        ++enemyIt; // 다음 Enemy로 이동
    }
}

void Player::updateAttack(std::vector<Enemy*>& enemies) {

    // 총알과 미사일의 상태 업데이트
    for (Bullet* bullet : bullets) {
        bullet->update(); // 발사체 상태 업데이트
    }
    for (Missile* missile : missiles) {
        missile->update(); // 발사체 상태 업데이트
    }

    // 아군 유닛의 발사체 업데이트
    for (Missile* Missile : allyMissiles) {
        Missile->update();
    }

    if (stageNumber == 2) {
        // 중앙에서 도달하면 적군 전체 제거
        if (std::any_of(allyMissiles.begin(), allyMissiles.end(), [](Missile* missile) {
            return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
            })) {
            // 적군 전체 삭제
            for (auto* enemy : enemies) {
                delete enemy;  // 동적 메모리 해제
            }
            enemies.clear(); // 적군 벡터 초기화
        }

        allyMissiles.erase(
            std::remove_if(allyMissiles.begin(), allyMissiles.end(),
                [](Missile* missile) {
                    return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
                }),
            allyMissiles.end()

        );
        
    }

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