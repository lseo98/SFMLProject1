#include "Player.h"
#include "Bullet.h" 
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;
                         // health,  speed, sf::Vector2f position
Player::Player() : Character(3, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 4.0f / 5.0f)) { 
    missileLaunched = false; 
}

void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // 위치 업데이트

    // 플레이어가 설정 화면 바깥으로 나갈 경우 예외 처리
    if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
    if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width;
    if (this->position.y < 0)  this->position.y = 0;
    if (this->position.y + height > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - height;

}


void Player::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}
//방향에 따라서 사진 업로드
void Player::updateDirection(char direction, int stageNumber) {
    if (direction != this->direction) { //버벅거림 막기
        this->direction = direction;
        if (stageNumber == 2) { // Only change image in stage 3
            if (direction == 'A') {
                image("sea_my_unit_left.png");
            }
            else if (direction == 'D') {
                image("sea_my_unit_right.png");
            }
        }
        if (stageNumber == 3) { // Only change image in stage 3
            if (direction == 'A') {
                image("land_my_unit_left.png");
            }
            else if (direction == 'D') {
                image("land_my_unit_right.png");
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

void Player::setPlayer(int stageNumber){
    std::string textureFile;
    
    // 기존 공격체 삭제
    bullets.clear();
    missiles.clear();
    
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
        textureFile ="land_my_unit_right.PNG";
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
    width = sprite.getTexture()->getSize().x * sprite.getScale().x;     // 
    height = sprite.getTexture()->getSize().y * sprite.getScale().y;
}


void Player::basic_attack() {

    // 플레이어의 중앙 위치를 계산하여 총알의 시작 위치로 사용
    sf::Vector2f bulletStartPosition = this->position;
    bulletStartPosition.x += width / 2.0f; // 플레이어의 중심 x 좌표
    bulletStartPosition.y += height / 2.0f; // 플레이어의 중심 y 좌표
    bullets.emplace_back(new Bullet(bulletStartPosition, bulletDirection, 10.0f));
    //bullets.push_back(Bullet(bulletStartPosition, bulletDirection, 1.0f));


}




void Player::special_attack() {

    if (!missileLaunched) {                                                 // 미사일이 없는 경우
        // 플레이어의 중앙 위치를 계산하여 미사일의 시작 위치로 사용
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += width / 2.0f; // 플레이어의 중심 x 좌표
        missileStartPosition.y += height / 2.0f; // 플레이어의 중심 y 좌표

        missiles.emplace_back(new Missile(missileStartPosition, missileDirection, 1.0f));
       // missileLaunched = true;

    }
}

void Player::ultimate_attack() {

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

        // Bullet 처리
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {

            if ((*bulletIt)->shape.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // 충돌 발생 시

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

        ++enemyIt; // 다음 Enemy로 이동
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

}


void Player::renderAttack(sf::RenderWindow& window) {
    for (Bullet *bullet : bullets) {
        bullet->draw(window); // 발사체 상태 업데이트
    }
    for (Missile *missile : missiles) {
        missile->draw(window); // 발사체 상태 업데이트
    }
}