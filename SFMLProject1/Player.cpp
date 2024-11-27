#include "Player.h"
#include "Bullet.h" 
#include <iostream>

extern int WINDOWWIDTH, WINDOWHEIGHT;
                         // health,  speed, sf::Vector2f position
Player::Player() : Character(3, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 4.0f / 5.0f)) { 
    missileLaunched = false; 
}

void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // ��ġ ������Ʈ

    // �÷��̾ ���� ȭ�� �ٱ����� ���� ��� ���� ó��
    if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
    if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width;
    if (this->position.y < 0)  this->position.y = 0;
    if (this->position.y + height > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - height;

}


void Player::draw(sf::RenderWindow& window) {
    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}
//���⿡ ���� ���� ���ε�
void Player::updateDirection(char direction, int stageNumber) {
    if (direction != this->direction) { //�����Ÿ� ����
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
        bulletDirection.x *= -1.0f;    // �Ѿ� ���� ��ȯ - ���� �̰ɷ� �����ϵ��� �����ؾ�. 
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
    
    // ���� ����ü ����
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
    
    // ����ü ���� �ʱ�ȭ
    //this->bulletDirection = bulletDirection;
    //this->missileDirection = missileDirection;
    bulletDirection = bulletDirection;
    missileDirection = missileDirection;

    // �÷��̾� �̹��� ó��
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

    // �÷��̾��� �߾� ��ġ�� ����Ͽ� �Ѿ��� ���� ��ġ�� ���
    sf::Vector2f bulletStartPosition = this->position;
    bulletStartPosition.x += width / 2.0f; // �÷��̾��� �߽� x ��ǥ
    bulletStartPosition.y += height / 2.0f; // �÷��̾��� �߽� y ��ǥ
    bullets.emplace_back(new Bullet(bulletStartPosition, bulletDirection, 10.0f));
    //bullets.push_back(Bullet(bulletStartPosition, bulletDirection, 1.0f));


}




void Player::special_attack() {

    if (!missileLaunched) {                                                 // �̻����� ���� ���
        // �÷��̾��� �߾� ��ġ�� ����Ͽ� �̻����� ���� ��ġ�� ���
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += width / 2.0f; // �÷��̾��� �߽� x ��ǥ
        missileStartPosition.y += height / 2.0f; // �÷��̾��� �߽� y ��ǥ

        missiles.emplace_back(new Missile(missileStartPosition, missileDirection, 1.0f));
       // missileLaunched = true;

    }
}

void Player::ultimate_attack() {

}

void Player::collision(std::vector<Enemy*>& enemies) {
    // �÷��̾��� ���ݰ� ������ �浹 ó��
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
        bool enemyDestroyed = false;

        if (*enemyIt == nullptr) {  // nullptr üũ
            enemyIt = enemies.erase(enemyIt);
            continue;
        }

        // Missile ó��   // �̻����� ������ �Ѿ˿� ���� ���� ���� ���� ������ ���� continue�� ���� �߻��� �� �־� �Ѿ˺��� �켱 �浹ó��
        for (auto missileIt = missiles.begin(); missileIt != missiles.end();) {
            if (*missileIt == nullptr) {  // nullptr üũ
                missileIt = missiles.erase(missileIt);
                continue;
            }
            if ((*missileIt)->shape.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��
                sf::FloatRect boundsMissile = (*missileIt)->shape.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);

                for (auto enemyTmpIt = enemies.begin(); enemyTmpIt != enemies.end(); ) {
                    if (*enemyTmpIt == nullptr) {  // nullptr üũ
                        enemyTmpIt = enemies.erase(enemyTmpIt);
                        continue;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                    if (distance < (*missileIt)->getRange()) {

                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����



                        if ((*enemyTmpIt)->getHealth() <= 0) {
                            delete* enemyTmpIt;                                // ���� �޸� ����
                            enemyTmpIt = enemies.erase(enemyTmpIt);            // Enemy ����

                            enemyDestroyed = true;
                        }
                    }
                    else enemyTmpIt++;

                }
                delete* missileIt;                                     // ���� �޸� ����
                missileIt = missiles.erase(missileIt);                 // Bullet ���� �� ���� ��Ҹ� ����Ŵ
                /////////
                return;  // enemy�� �����Ǹ� ���� �ٱ� for������ ������ �߻��ϴ� ���ؼ� �׳� �̻��� ���� ó�� �Ǹ� ������Ʈ�� ����            
                ////////
            }
            else {                                                  // �浹�� �߻����� ���� ��� �̻��� ������Ʈ
                // �ſ� �߿�
                // (*missileIt)->update(); // Missile ���¸� �浹 ó�� ���ο��� ������Ʈ �� ��� ������ ���� ��� ������Ʈ�� ���� ���� �� �ִ�
                ++missileIt;
            }
        }
        if (enemyDestroyed) {
            continue; // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �̵�
        }

        // Bullet ó��
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {

            if ((*bulletIt)->shape.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��

                /*std::cout << "Bullet Global Bounds: " << (*bulletIt)->shape.getGlobalBounds().left << ", "
                    << (*bulletIt)->shape.getGlobalBounds().top << ", "
                    << (*bulletIt)->shape.getGlobalBounds().width << ", "
                    << (*bulletIt)->shape.getGlobalBounds().height << std::endl;

                std::cout << "Enemy Global Bounds: " << (*enemyIt)->sprite.getGlobalBounds().left << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().top << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().width << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().height << std::endl;*/

                (*enemyIt)->takeDamage((*bulletIt)->getDamage());   // Enemy�� ü�� ����
                delete* bulletIt;                                   // ���� �޸� ����
                bulletIt = bullets.erase(bulletIt);                 // Bullet ���� �� ���� ��Ҹ� ����Ŵ

                if ((*enemyIt)->getHealth() <= 0) {
                    delete* enemyIt;                                // ���� �޸� ����
                    enemyIt = enemies.erase(enemyIt);               // Enemy ����

                    enemyDestroyed = true;
                    break;                                          // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �� �̻��� �浹 �˻� ���ʿ�
                }
            }
            else {                                                  // �浹�� �߻����� ���� ��� �Ѿ� ������Ʈ
                // �ſ� �߿�
                // (*bulletIt)->update(); // Bullet ���¸� �浹 ó�� ���ο��� ������Ʈ �� ��� ������ ���� ��� ������Ʈ�� ���� ���� �� �ִ�
                ++bulletIt;
            }
        }
        if (enemyDestroyed) {
            continue; // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �̵�
        }

        ++enemyIt; // ���� Enemy�� �̵�
    }
}

void Player::updateAttack() {
   
    // �Ѿ˰� �̻����� ���� ������Ʈ
    for (Bullet* bullet : bullets) {
        bullet->update(); // �߻�ü ���� ������Ʈ
    }
    for (Missile* missile : missiles) {
        missile->update(); // �߻�ü ���� ������Ʈ
    }

}


void Player::renderAttack(sf::RenderWindow& window) {
    for (Bullet *bullet : bullets) {
        bullet->draw(window); // �߻�ü ���� ������Ʈ
    }
    for (Missile *missile : missiles) {
        missile->draw(window); // �߻�ü ���� ������Ʈ
    }
}