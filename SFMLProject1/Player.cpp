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

void Player::takeDamage(float amount) {
    this->health -= 1;
    if (this->health < 0) this->health = 0;
    std::cout << "�÷��̾� ü�� : " << this->health << std::endl;
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

void Player::updateAttack(std::vector<Enemy*> &enemies) {

    // �÷��̾��� ���ݰ� ������ �浹 ó��
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
        bool enemyDestroyed = false;

        if (*enemyIt == nullptr) {  // nullptr üũ
            enemyIt = enemies.erase(enemyIt);
           continue;
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

        // Missile ó��
        for (auto missileIt = missiles.begin(); missileIt != missiles.end();) {

            if ((*missileIt)->shape.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��

                (*enemyIt)->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����
                delete* missileIt;                                   // ���� �޸� ����
                missileIt = missiles.erase(missileIt);                 // Bullet ���� �� ���� ��Ҹ� ����Ŵ


                if ((*enemyIt)->getHealth() <= 0) {
                    delete* enemyIt;                                // ���� �޸� ����
                    enemyIt = enemies.erase(enemyIt);               // Enemy ����

                    enemyDestroyed = true;
                    break;                                          // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �� �̻��� �浹 �˻� ���ʿ�
                }
            }
            else {                                                  // �浹�� �߻����� ���� ��� �Ѿ� ������Ʈ
                // �ſ� �߿�
                // (*missileIt)->update(); // Missile ���¸� �浹 ó�� ���ο��� ������Ʈ �� ��� ������ ���� ��� ������Ʈ�� ���� ���� �� �ִ�
                ++missileIt;
            }
        }
        if (enemyDestroyed) {
            continue; // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �̵�
        }
        ++enemyIt; // ���� Enemy�� �̵�
 
    }

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