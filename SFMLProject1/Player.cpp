#include "Player.h"
#include "Boss.h" 
#include "Bullet.h" 
#include "Missile.h"
#include "Game.h"
#include <iostream>  

extern int WINDOWWIDTH, WINDOWHEIGHT;
// health,  speed, sf::Vector2f position
Player::Player() : Character(5, 15.0f, sf::Vector2f(WINDOWWIDTH / 2.0f, WINDOWHEIGHT * 9.0f / 10.0f)) {
    //missileLaunched = false; 

    // Ư�� ���� ���� ���� �ʱ�ȭ
    specialAttackCooldown = 1.0f; // Ư�� ���� ��Ÿ��: 1��
    //timeSinceLastSpecial = specialAttackCooldown; // ���� ���� �� �ٷ� ����� �� �ֵ��� ����
    canSpecialAttack = false;

    ultimateAttackCooldown = 20.0f; // �ʻ�� ��Ÿ�� 20��
    canUltimateAttack = false;

    waitTime = 0.0f; // �ʱ�ȭ

    killCountNomalUnit = 0;
    killCountEliteUnit1 = 0;
    killCountEliteUnit2 = 0;
    killCountEliteUnit3 = 0;


    initializeHearts();
}



void Player::move(sf::Vector2f updatePosition) {
    this->position += updatePosition;   // ��ġ ������Ʈ

    if (stageNumber == 1 || stageNumber == 3 ) {
        // �÷��̾ ���� ȭ�� �ٱ����� ���� ��� ���� ó��
        if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
        if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width;
        if (this->position.y < 0)  this->position.y = 0;
        if (this->position.y + height > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - height;
    }
    else if (stageNumber == 2) {
        // �÷��̾ ���� �������
        this->position.y += 0.01f;
        // �÷��̾ ���� ȭ�� �ٱ����� ���� ��� ���� ó��
        if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
        if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width;
        if (this->position.y < 240)  this->position.y = 240;
        if (this->position.y + height > WINDOWHEIGHT + 40) {
            this->position.y = WINDOWHEIGHT - height - 100;
            if (!isOnGround) { // ü�� ���Ұ� �ߺ� ȣ����� �ʵ���
                takeDamage(1.0f);
                isOnGround = true; // �̹� ó���� ���·� ����
                // ü�� ���ҿ� ���� ��Ʈ ���¸� ��� ������Ʈ
                hearts.clear();
                for (int i = 0; i < this->health; i++) {
                    sf::Sprite heartSprite;
                    heartSprite.setTexture(heartTexture);
                    heartSprite.setScale(0.05f, 0.05f); // ��Ʈ ũ�� ����
                    heartSprite.setPosition(1400.0f + i * 70.0f, 15.0f); // ��Ʈ ��ġ ���� (x�� ���� ����)
                    hearts.push_back(heartSprite);
                }
            }
        }
        else {
            isOnGround = false; // �������� ������ �ٽ� �ʱ�ȭ
        }
    }
    if (stageNumber == 4) {
        // �÷��̾ ���� ȭ�� �ٱ����� ���� ��� ���� ó��
        if (this->position.x < WINDOWWIDTH / 4.0f) this->position.x = WINDOWWIDTH / 4.0f;
        if (this->position.x + width > WINDOWWIDTH / 4.0f * 3.0f - 250) this->position.x = WINDOWWIDTH / 4.0f * 3.0f - width - 250;
        if (this->position.y < 0)  this->position.y = 0;
        if (this->position.y + height > WINDOWHEIGHT) this->position.y = WINDOWHEIGHT - height;
    }
   // std::cout << "�������� 4���� �̵� ó�� " << stageNumber <<  std::endl;
}


void Player::initializeHearts() {
    if (!heartTexture.loadFromFile("heart.png")) {
        std::cerr << "Error loading heart texture!" << std::endl;
        return;
    }
    loadProjectileTextures(); // �ؽ�ó �ε� �߰�
    loadExplosionTextures();

    // �÷��̾� ü�¸�ŭ ��Ʈ�� �߰�
    changeHeartSprite();
}

void Player::changeHeartSprite() {
    hearts.clear();
    for (int i = 0; i < this->health; i++) {
        sf::Sprite heartSprite;
        heartSprite.setTexture(heartTexture);
        heartSprite.setScale(0.05f, 0.05f); // ��Ʈ ũ�� ����
        heartSprite.setPosition(1400.0f + i * 70.0f, 15.0f); // ��Ʈ ��ġ ���� (x�� ���� ����)
        hearts.push_back(heartSprite);

    }
}
void Player::draw(sf::RenderWindow& window) {
    // ��Ʈ ��������Ʈ �׸���
    for (const sf::Sprite& heart : hearts) {

        window.draw(heart);
    }

    if (isBlinking && !isVisible) {
        return; // ������ ���¿��� ������ ��� �ƹ��͵� �׸��� ����
    }

    this->sprite.setPosition(this->position);
    window.draw(this->sprite);
}

void Player::triggerBlink() {
    isBlinking = true;         // ������ Ȱ��ȭ
    isVisible = true;          // ó���� ���̴� ����
    blinkClock.restart();      // Ÿ�̸� �ʱ�ȭ
}

void Player::updateBlink() {
    if (isBlinking) {
        float elapsed = blinkClock.getElapsedTime().asSeconds();
        // ������ ����
        if (elapsed > blinkDuration) {
            isBlinking = false; // ������ ��Ȱ��ȭ
            isVisible = true;   // �׻� ���̴� ���·� ����
            return;
        }
        // �����̴� ���ݿ� ���� ���ü� ���
        if (static_cast<int>(elapsed / blinkInterval) % 2 == 0) {
            isVisible = true;  // ���̴� ����
        }
        else {
            isVisible = false; // ������ ����
        }
    }
}

void Player::takeDamage(float amount) {
    if (Game::bossDefeated) {
        return; // ���� �й� �� �÷��̾� ������ ����
    }
    // �θ� Ŭ������ takeDamage ȣ��
    Character::takeDamage(amount);
    // ü���� �������� �� �߰� ���� ����
    if (getHealth() > 0) {
        triggerBlink(); // ������ ȿ�� Ȱ��ȭ
    }
}

//���⿡ ���� ���� ���ε�
void Player::updateDirection(char direction, int stageNumber) {
    if (direction != this->direction) { //�����Ÿ� ����
        this->direction = direction;
        sf::IntRect textureRect;  // ǥ���� �ؽ�ó ����
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
        if (stageNumber == 3 || stageNumber == 4) { // Only change image in stage 3
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
        bulletDirection.x *= -1.0f;    // �Ѿ� ���� ��ȯ - ���� �̰ɷ� �����ϵ��� �����ؾ�. 
    }

}
void Player::image(std::string textureFile, const sf::IntRect& textureRect) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture: " << textureFile << std::endl;
    }
    else {
        sprite.setTexture(texture);   // �ؽ�ó�� ��������Ʈ�� ����
        // �ؽ�ó ������ ������ ��� �ش� ������ ���
        if (textureRect != sf::IntRect()) {
            sprite.setTextureRect(textureRect);
        }
        sprite.setScale(0.1f, 0.1f);
    }
}

void Player::setPlayer(int stageNumber) {
    std::string textureFile;

    // ���� ����ü ����
    bullets.clear();
    missiles.clear();

    allyMissiles.clear(); // �Ʊ� �߻�ü�� ����
    allyUnits.clear();   // ���� �Ʊ� ���� ���� 
    clearExplosions();   // ���� �ִϸ��̼� ����


    this->stageNumber = stageNumber;
        sf::IntRect textureRect;  // ǥ���� �ؽ�ó ����
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
    case 4:
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

    // ����ü ���� �ʱ�ȭ
    //this->bulletDirection = bulletDirection;
    //this->missileDirection = missileDirection;
    bulletDirection = bulletDirection;
    missileDirection = missileDirection;

    
    width = sprite.getTexture()->getSize().x * sprite.getScale().x;
    height = sprite.getTexture()->getSize().y * sprite.getScale().y;
}
void Player::restart() {
    health = 5;

    Game::globalClock.restart();
    //printf("%lf", Game::globalClock);
    canSpecialAttack = false;
    timeSinceLastSpecial = 0;
    canUltimateAttack = false;
    timeSinceLastUltimate = 0;

    changeHeartSprite();
    setPlayer(1);
    setPosition(sf::Vector2f(WINDOWWIDTH / 2.0f - width / 2.0f, WINDOWHEIGHT * 4.0f / 5.0f));
    stageNumber = 1;
    killCountNomalUnit = 0;
    /*killCountEliteUnit1 = 0;
    killCountEliteUnit2 = 0;
    killCountEliteUnit3 = 0;*/
}

void Player::basicAttack() {

    // �÷��̾��� �߾� ��ġ�� ����Ͽ� �Ѿ��� ���� ��ġ�� ���
    if (stageNumber == 1) {
        bulletStartPosition = sf::Vector2f(this->position.x + 43, this->position.y);
    }
    if (stageNumber == 2) {
        bulletStartPosition = sf::Vector2f(this->position.x + 50, this->position.y + 30);
        //sf::Vector2f bulletStartPosition(this->position.x + 200, this->position.y+100);
    }
    if (stageNumber == 3 || stageNumber == 4) {
        bulletStartPosition = sf::Vector2f(this->position.x + 20, this->position.y + 15);
        //sf::Vector2f bulletStartPosition(this->position.x + 20, this->position.y+20);
    }

    //  bullets.emplace_back(new Bullet(bulletStartPosition, bulletDirection, 10.0f));
      //bullets.push_back(Bullet(bulletStartPosition, bulletDirection, 1.0f));
   
    sf::IntRect textureRect;  // ǥ���� �ؽ�ó ����
        // ���� ���������� �´� �ؽ�ó�� �߻�ü�� ����
    Bullet* bullet = new Bullet(bulletStartPosition, bulletDirection, 10.0f);
    bullet->setTexture(bulletTextures[stageNumber - 1], textureRect); // �ؽ�ó ����
    bullets.emplace_back(bullet);
    //  std::cout << "Bullet created at position: " << bulletStartPosition.x << ", " << bulletStartPosition.y << std::endl;

}

void Player::specialAttack() {
    /*std::cout << "Nomal Unit óġ �� : " << killCountNomalUnit << std::endl;
    std::cout << "stage1 Elite Unit óġ �� : " << killCountEliteUnit1 << std::endl;
    std::cout << "stage2 Elite Unit óġ �� : " << killCountEliteUnit2 << std::endl;
    std::cout << "stage3 Elite Unit óġ �� : " << killCountEliteUnit3 << std::endl << std::endl;*/

    if (canSpecialAttack) {
        // �÷��̾��� �߾� ��ġ�� ����Ͽ� �̻����� ���� ��ġ�� ���
        sf::Vector2f missileStartPosition = this->position;
        missileStartPosition.x += width / 2.0f; // �÷��̾��� �߽� x ��ǥ
        missileStartPosition.y += height / 2.0f; // �÷��̾��� �߽� y ��ǥ
        sf::IntRect textureRect;  // ǥ���� �ؽ�ó ����
        // �̻��� ���� �� ����
        if (direction == 'A' && stageNumber == 2) missileDirection = sf::Vector2f(-1.0f, 0.0f);
        else if (direction == 'D' && stageNumber == 2) missileDirection = sf::Vector2f(1.0f, 0.0f);
        Missile* missile = new Missile(missileStartPosition, missileDirection, 8.0f);
        missile->isPlayerProjectile = true;
        missile->setTexture(MissileTextures[stageNumber - 1], textureRect); // �ؽ�ó ����
        missiles.push_back(missile);

        // Ư�� ���� ���� ����
        timeSinceLastSpecial = 0.0f;  // ��Ÿ�� �ʱ�ȭ
        canSpecialAttack = false;     // ��Ÿ�� ����
       // std::cout << "Special attack activated!" << std::endl;
    }
    else {
       // std::cout << "Special attack on cooldown!" << std::endl;
    }

}


void Player::ultimateAttack() {
    if (canUltimateAttack) {
        switch (stageNumber) {
        case 1: // �ϴ� ��������
        {
            //std::cout << "Sky ultimate attack activated!" << std::endl;

            // ��� �ð� �ʱ�ȭ
            waitTime = 5.0f;  // �ϴ� �������������� 5�� ���

            //// �÷��̾� ��ġ�� �߾� �ϴ����� ����
            //this->position = sf::Vector2f(WINDOWWIDTH / 2.0f - width / 2.0f, WINDOWHEIGHT - height);
            //this->sprite.setPosition(this->position);

            // �Ʊ� ���� �ؽ�ó �ε�
            if (!allyTexture.loadFromFile("sky_p_unit.PNG")) { /// �̹��� �ٲ�� �� 
                std::cerr << "Error loading texture for ally units." << std::endl;
                return; // �ؽ�ó�� �ε����� ���ϸ� �Լ� ����
            }
            float halfWidth = allyTexture.getSize().x * sprite.getScale().x / 2.0f;

            // �Ʊ� ���� ���� �� �ʱ� ��ġ ���� (�̹��� ������ �� x ������ ����)
            sf::Vector2f leftWingPosition1(600.0f - halfWidth, 900.0f);
            sf::Vector2f leftWingPosition2(750.0f - halfWidth, 900.0f);
            sf::Vector2f rightWingPosition1(1050.0f - halfWidth, 900.0f);
            sf::Vector2f rightWingPosition2(1200.0f - halfWidth, 900.0f);
            std::vector<sf::Vector2f> allyPositions = { leftWingPosition1, leftWingPosition2, rightWingPosition1, rightWingPosition2 };

            // �Ʊ� ���� ����
            allyUnits.clear(); // ���� �Ʊ� ���� ����
            for (const auto allyPosition : allyPositions) {
                sf::Sprite allySprite;
                allySprite.setTexture(allyTexture);
                allySprite.setPosition(allyPosition);
                allySprite.setScale(0.1f, 0.1f);
                allyUnits.push_back(allySprite);
            }

            // �ʻ�� ���� ����
            timeSinceLastUltimate = 0.0f;  // ��Ÿ�� �ʱ�ȭ
            canUltimateAttack = false;     // ��Ÿ�� ����
        }
        break;

        case 2: // �ٴ� ��������
        {
            //// �� ��������ó�� �̵��ϸ�(���� ������) ��� ����
            //std::cout << "Sea ultimate attack activated!" << std::endl;

            //// ���ݱ� �ؽ�ó �ε�
            //if (!allyTexture.loadFromFile("land_p_unit.png")) { // ���ݱ� �̹��� �ؽ�ó �ε�
            //    std::cerr << "Error loading texture for aircraft units." << std::endl;
            //    return; // �ؽ�ó �ε� ���� �� �Լ� ����
            //}

            //// ���ݱ� ���� �� �ʱ� ��ġ ���� (������ ��ܿ��� ����)
            //sf::Vector2f aircraftStartPosition(450, 160.0f); // ���� ��ܿ��� ����
            //sf::Sprite aircraftSprite;
            //aircraftSprite.setTexture(allyTexture);
            //aircraftSprite.setPosition(aircraftStartPosition);
            //aircraftSprite.setScale(0.1f, 0.1f);

            //// �Ʊ� ���� ���Ϳ� �߰�
            //allyUnits.clear(); // ���� �Ʊ� ���� ����
            //allyUnits.push_back(aircraftSprite);

            //// �ʻ�� ���� ����
            //timeSinceLastUltimate = 0.0f;  // ��Ÿ�� �ʱ�ȭ
            //canUltimateAttack = false;     // ��Ÿ�� ����


            // �߻�ü �ϳ� �߾ӿ��� ����
            //std::cout << "Sea ultimate attack activated!" << std::endl;

            // �߻�ü �ʱⰪ ����
            sf::Vector2f missileStartPosition(400, 600); // ���� ������ ����
            sf::Vector2f missileDirection(1.0f, 0.0f); // ���������� ���� �̵�
            float missileSpeed = 3.0f;  // �߻� �ӵ� (�ٴ� ��������)
            Missile* missile = new Missile(missileStartPosition, missileDirection, missileSpeed);
            missile->isPlayerProjectile = false;
            sf::IntRect textureRect;
            missile->setTexture(AllMissileTextures[stageNumber - 1], textureRect);
            // ������ ����� �ӵ��� �߻�ü ����
            allyMissiles.emplace_back(missile);

            // �ʻ�� ���� ����
            timeSinceLastUltimate = 0.0f;  // ��Ÿ�� �ʱ�ȭ 
            canUltimateAttack = false;     // ��Ÿ�� ����
        }
        break;

        case 3: // �� ��������
        case 4: // ���� ��������
        {
            //std::cout << "Land ultimate attack activated!" << std::endl;

            // ���ݱ� �ؽ�ó �ε�
            if (!allyTexture.loadFromFile("land_p_unit.png")) { // ���ݱ� �̹��� �ؽ�ó �ε�
                std::cerr << "Error loading texture for aircraft units." << std::endl;
                return; // �ؽ�ó �ε� ���� �� �Լ� ����
            }

            // ���ݱ� ���� �� �ʱ� ��ġ ���� (������ ��ܿ��� ����)
            sf::Vector2f aircraftStartPosition(WINDOWWIDTH - 450, 50.0f); // ������ ��ܿ��� ����
            sf::Sprite aircraftSprite;
            aircraftSprite.setTexture(allyTexture);
            aircraftSprite.setPosition(aircraftStartPosition);
            aircraftSprite.setScale(0.2f, 0.2f);

            // �Ʊ� ���� ���Ϳ� �߰�
            allyUnits.clear(); // ���� �Ʊ� ���� ����
            allyUnits.push_back(aircraftSprite);

            // �ʻ�� ���� ����
            timeSinceLastUltimate = 0.0f;  // ��Ÿ�� �ʱ�ȭ
            canUltimateAttack = false;     // ��Ÿ�� ����
        }
        break;

        default:
            //std::cout << "Invalid stage number for ultimate attack!" << std::endl;
            break;
        }
    }
    else {
       // std::cout << "Ultimate attack on cooldown!" << std::endl;
    }
}

void Player::allyAttack() {
    for (const auto& ally : allyUnits) {
        sf::Vector2f missileStartPosition = ally.getPosition();
        sf::Vector2f missileDirection;
        float missileSpeed, missileRange, missileDamage;
        sf::Texture missileTexture; // �ؽ�ó �ε�� ����
       

        if (stageNumber == 1) {  // �ϴ� ������������ �߻�ü �������� �߻�
            
            sf::Sprite allMiSprite;
            missileStartPosition.x += ally.getGlobalBounds().width / 2.0f;  // �Ʊ� ������ �߾� ��ġ���� �߻�
            missileStartPosition.y -= 10.0f;  // �ణ ���ʿ��� �߻�
            missileDirection = sf::Vector2f(0.0f, -1.0f);  // ���� ����
            missileSpeed = 5.0f;    // �߻� �ӵ� (�ϴ� ��������)
            missileRange = 100.0f;   // �̻��� �浹 ����
            missileDamage = 0.001f;  // �̻��� ���ݷ�
            //image = AllMissileTextures[0].copyToImage(); // �ϴ� ���������� �̹��� ����
            //missile->setTexture(AllMissileTextures[0], textureRect);
        }
        //else if (stageNumber == 2) {  // �ٴ� ������������ �߻�ü ���������� �߻�
        //    sf::Vector2f missileStartPosition(450, 600); // ���� ������ ����
        //    sf::Vector2f missileDirection(1.0f, 0.0f); // ���������� �߻�
        //    float missileSpeed = 3.0f;  // �߻� �ӵ� (�ٴ� ��������)
        //}
        else if (stageNumber == 3 || stageNumber == 4) {  // �� ������������ �߻�ü �Ʒ������� �߻�
            missileStartPosition.x += ally.getGlobalBounds().width / 2.0f;  // �Ʊ� ������ �߾� ��ġ���� �߻�
            missileStartPosition.y += ally.getGlobalBounds().height + 20.0f;  // �ణ �Ʒ��ʿ��� �߻�
            missileDirection = sf::Vector2f(0.0f, 1.0f);  // �Ʒ��� ����
            missileSpeed = 5.0f;  // �߻� �ӵ� (�� ��������)
            missileRange = 200.0f;   // �̻��� �浹 ����
            missileDamage = 300.0f;  // �̻��� ���ݷ�
            //image = AllMissileTextures[2].copyToImage();; // �� ���������� �̹��� ����
            //missile->setTexture(AllMissileTextures[2], textureRect);
        }
       
        //missileTexture.loadFromImage(image);

        // ������ ����� �ӵ��� �߻�ü ����
        Missile* missile = new Missile(missileStartPosition, missileDirection, missileSpeed);
        sf::IntRect textureRect;  // ǥ���� �ؽ�ó ����

        if (stageNumber == 4) missile->setTexture(AllMissileTextures[2], textureRect);
        else missile->setTexture(AllMissileTextures[stageNumber - 1], textureRect);

        missile->isPlayerProjectile = false;  // �Ʊ� �̻��Ϸ� ����
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
    // Ư�� ���� ��Ÿ�� ������Ʈ
    if (!canSpecialAttack) {
        timeSinceLastSpecial += dt; // ������ �� ��� �ð��� ����
        if (timeSinceLastSpecial >= specialAttackCooldown) {
            canSpecialAttack = true; // ��Ÿ�� ���� �� Ư�� ���� �����ϰ� ����
            //std::cout << "Special attack is ready!" << std::endl;
        }
    }

    // �ʻ�� ��Ÿ�� ������Ʈ
    if (!canUltimateAttack) {
        timeSinceLastUltimate += dt; // ������ �� ��� �ð��� ����
        if (timeSinceLastUltimate >= ultimateAttackCooldown) {
            canUltimateAttack = true; // ��Ÿ�� ���� �� �ʻ�� �����ϰ� ����
           // std::cout << "Ultimate attack is ready!" << std::endl;
        }
    }
}

void Player::updateAllies(float dt, std::vector<Enemy*>& enemies, std::vector<std::unique_ptr<Missile>>& globalMissiles) {
    switch (stageNumber) {
    case 1: // �ϴ� ��������
        // �ϴ� ������������ �Ʊ� ���� �������� ������ �̵�
        //for (auto& ally : allyUnits) {
        //    sf::Vector2f position = ally.getPosition();
        //    position.y -= 100.0f * dt; // �������� �̵� (�ӵ� 50.0f * delta time)
        //    ally.setPosition(position);
        //}

        //// ȭ�� ������ ���� �Ʊ� ���� ����
        //allyUnits.erase(
        //    std::remove_if(allyUnits.begin(), allyUnits.end(),
        //        [](sf::Sprite& ally) {
        //            return ally.getPosition().y + ally.getGlobalBounds().height < 0; // ȭ�� ���� ������ ���� ���
        //        }),
        //    allyUnits.end()
        //);
        // �ϴ� ������������ 5�� ���� ���ڸ��� �ִٰ�  �밢������ �̵�

    {
        // ��� �ð� üũ
        if (waitTime > 0.0f) {
            waitTime -= dt;

            // Y�� �̵�
            for (auto& ally : allyUnits) {
                sf::Vector2f position = ally.getPosition();
                position.y -= 100.0f * dt; // õõ�� �������� �̵�
                if (position.y < 700.0f) { // ������ ��ġ���� �̵�
                    position.y = 700.0f;
                }
                ally.setPosition(position);
            }
            return;  // ��� �ð��� ������ �������� �밢�� �̵� �� ��
        }

        // �ϴ� ������������ �Ʊ� ���� �밢�� �������� �̵�
        for (size_t i = 0; i < allyUnits.size(); ++i) {
            sf::Vector2f position = allyUnits[i].getPosition();
            if (i < allyUnits.size() / 2) {
                position.x -= 100.0f * dt; // ���� �� �밢������ �̵�
                position.y -= 50.0f * dt;
            }
            else {
                position.x += 100.0f * dt; // ������ �� �밢������ �̵�
                position.y -= 50.0f * dt;
            }
            allyUnits[i].setPosition(position);
        }

        allyUnits.erase(
            std::remove_if(allyUnits.begin(), allyUnits.end(),
                [](sf::Sprite& ally) {
                    return ally.getPosition().y < -50 || // ȭ�� ������ ��� ���
                        ally.getPosition().x < -50 || // ȭ�� ������ ��� ���
                        ally.getPosition().x > WINDOWWIDTH + 50 || // ȭ�� �������� ��� ���
                        ally.getPosition().y > WINDOWHEIGHT + 50; // ȭ�� �Ʒ����� ��� ���
                }),
            allyUnits.end()
        );

    }
    break;

    case 2: // �ٴ� ��������
        //// �ٴ� ������������ �Ʊ� ������ ���ʿ��� ���������� �̵�
        //for (auto& ally : allyUnits) {
        //    sf::Vector2f position = ally.getPosition();
        //    position.x += 100.0f * dt; // ���������� �̵� (�ӵ� 100.0f * delta time)
        //    ally.setPosition(position);
        //}

        //// ȭ�� ������ ���� �Ʊ� ���� ����
        //allyUnits.erase(
        //    std::remove_if(allyUnits.begin(), allyUnits.end(),
        //        [](sf::Sprite& ally) {
        //            return ally.getPosition().x > WINDOWWIDTH; // ȭ�� ������ ������ ���� ���
        //        }),
        //    allyUnits.end()
        //);

         // �ʻ�� �߾ӿ� �����ϸ� ���� ��ü ����
        if (std::any_of(allyMissiles.begin(), allyMissiles.end(), [](Missile* missile) {
            return missile->position.x >= WINDOWWIDTH / 2.0f ;
            })) {

            createExplosion(sf::Vector2f(450.0f, 0.0f), ExplosionType::Q_missileImpact);

            // ���� ��ü ����
            for (auto* enemy : enemies) {
                if (dynamic_cast<NormalUnit*>(enemy) == enemy) killCountNomalUnit++;
                else if (dynamic_cast<EliteUnit*>(enemy) == enemy) this->countKillElite();
                delete enemy;  // ���� �޸� ����
            }
            enemies.clear(); // ���� ���� �ʱ�ȭ

            for (auto& enemyMissile : globalMissiles) {
                //delete enemyMissile;  // ���� �޸� ����
            }
            globalMissiles.clear(); // ���� ����ü ���� �ʱ�ȭ

        }

        allyMissiles.erase(
            std::remove_if(allyMissiles.begin(), allyMissiles.end(),
                [](Missile* missile) {
                    return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
                }),
            allyMissiles.end()

        );
    
            break;

    case 3: // �� ��������
    case 4: // ���� ��������
        for (auto& ally : allyUnits) {
            sf::Vector2f position = ally.getPosition();
            position.x -= 150.0f * dt; // �������� �̵� (�ӵ� 50.0f * delta time)
            ally.setPosition(position);
        }

        // ȭ�� ������ ���� �Ʊ� ���� ����
        allyUnits.erase(
            std::remove_if(allyUnits.begin(), allyUnits.end(),
                [](sf::Sprite& ally) {
                    return ally.getPosition().x > WINDOWWIDTH; // ȭ�� ������ ������ ���� ���
                }),
            allyUnits.end()
        );
        break;

    default:
        break;
    }
}

void Player::collision(std::vector<Enemy*>& enemies) {
    // �÷��̾��� ���ݰ� ������ �浹 ó��
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); enemyIt++) {
        bool enemyDestroyed = false;

        if (*enemyIt == nullptr) {  // nullptr üũ
            return;
        }

        // Missile ó��   // �̻����� ������ �Ѿ˿� ���� ���� ���� ���� ������ ���� continue�� ���� �߻��� �� �־� �Ѿ˺��� �켱 �浹ó��
        for (auto missileIt = missiles.begin(); missileIt != missiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr üũ
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);
                sf::Vector2f missiletopcenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top);
                
                createExplosion(missiletopcenter, ExplosionType::MissileImpact);
                
                for (auto enemyTmpIt = enemies.begin(); enemyTmpIt != enemies.end(); enemyTmpIt++) {
                    if (*enemyTmpIt == nullptr) {  // nullptr üũ
                        break;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                    if (distance < (*missileIt)->getRange()) {

                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����

                        if ((*enemyTmpIt)->getHealth() <= 0) {
                            createExplosion(tmpEnemyCenter, ExplosionType::EnemyDestroyed);
                            enemyDestroyed = true;
                            //if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                           // else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                            enemyDestroyed = true;
                        }
                    }

                }
                (*missileIt)->crashed();    // �̻��� �浹 ������ ���� ����
                
            }
        }
        if (enemyDestroyed) {
            continue; // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �̵�
        }

        // Bullet ó��
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++) {
            if ((*bulletIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��

                /*std::cout << "Bullet Global Bounds: " << (*bulletIt)->shape.getGlobalBounds().left << ", "
                    << (*bulletIt)->shape.getGlobalBounds().top << ", "
                    << (*bulletIt)->shape.getGlobalBounds().width << ", "
                    << (*bulletIt)->shape.getGlobalBounds().height << std::endl;

                std::cout << "Enemy Global Bounds: " << (*enemyIt)->sprite.getGlobalBounds().left << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().top << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().width << ", "
                    << (*enemyIt)->sprite.getGlobalBounds().height << std::endl;*/

                float damage = (*bulletIt)->getDamage();
                if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) damage /= 2.0f;

                (*enemyIt)->takeDamage(damage);   // Enemy�� ü�� ����
                (*bulletIt)->crashed();
                if ((*enemyIt)->getHealth() <= 0) {
                    createExplosion(((*enemyIt)->sprite.getPosition()), ExplosionType::EnemyDestroyed);
                    enemyDestroyed = true;
                    //if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                    //else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                    break;
                }
            }
        }

        // �ʻ�� Missile ó��   
        if (stageNumber != 2) {
            for (auto missileIt = allyMissiles.begin(); missileIt != allyMissiles.end(); missileIt++) {
                if (*missileIt == nullptr) {  // nullptr üũ
                    break;
                }
                if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��
                    sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                    sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                    //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);
                    //createExplosion(missileCenter, stageNumber);

                    for (auto enemyTmpIt = enemies.begin(); enemyTmpIt != enemies.end(); enemyTmpIt++) {
                        if (*enemyTmpIt == nullptr) {  // nullptr üũ
                            break;
                        }
                        sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                        sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                        sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                        double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                        if (distance < (*missileIt)->getRange()) {

                            (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����
                            createExplosion(tmpEnemyCenter, ExplosionType::EnemyDestroyed);
                            enemyDestroyed = true;
                            // �� ���Ŀ� �浹ó�� �� ���� �����Ƿ� ������ �ı� �Ǿ����� ���δ� �� �ʿ� ����
                            /*if ((*enemyTmpIt)->getHealth() <= 0) {
                                if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                                else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                            }*/
                        }

                    }
                    (*missileIt)->crashed();    // �̻��� �浹 ������ ���� ����

                }
            }
        }


    }

    deleteThisProjectile();

}

void Player::healUnitCollision(std::vector<HealUnit*> healUnits) {
    // �÷��̾��� ���ݰ� ������ �浹 ó��
    for (auto enemyIt = healUnits.begin(); enemyIt != healUnits.end(); enemyIt++) {
        bool enemyDestroyed = false;
        if (*enemyIt == nullptr) {  // nullptr üũ
            return;
        }
        // Missile ó��   // �̻����� ������ �Ѿ˿� ���� ���� ���� ���� ������ ���� continue�� ���� �߻��� �� �־� �Ѿ˺��� �켱 �浹ó��
        for (auto missileIt = missiles.begin(); missileIt != missiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr üũ
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                createExplosion(missileCenter, ExplosionType::MissileImpact);

                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);
                for (auto enemyTmpIt = healUnits.begin(); enemyTmpIt != healUnits.end(); enemyTmpIt++) {
                    if (*enemyTmpIt == nullptr) {  // nullptr üũ
                        break;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);
                    if (distance < (*missileIt)->getRange()) {
                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����
                        if ((*enemyTmpIt)->getHealth() <= 0) {
                            sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                            sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);

                            //if (dynamic_cast<NormalUnit*>(*enemyIt) == *enemyIt) killCountNomalUnit++;
                           // else if (dynamic_cast<EliteUnit*>(*enemyIt) == *enemyIt) killCountEliteUnit++;
                            createExplosion(tmpEnemyCenter, ExplosionType::EnemyDestroyed);

                            enemyDestroyed = true;
                        }
                    }
                }
                (*missileIt)->crashed();    // �̻��� �浹 ������ ���� ����
            }
        }
        if (enemyDestroyed) {

            continue; // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �̵�
        }
        // �ʻ�� Missile ó��   
        for (auto missileIt = allyMissiles.begin(); missileIt != allyMissiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr üũ
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                //sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);
                for (auto enemyTmpIt = healUnits.begin(); enemyTmpIt != healUnits.end(); enemyTmpIt++) {
                    if (*enemyTmpIt == nullptr) {  // nullptr üũ
                        break;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);
                    if (distance < (*missileIt)->getRange()) {
                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����
                    }
                }
                (*missileIt)->crashed();    // �̻��� �浹 ������ ���� ����
            }
        }

    }
    deleteThisProjectile();
}

void Player::shieldCollision(std::vector<Shield*> shield) {
    for (Shield* shield : shield) {
        for (auto bullet : bullets) {
            if (bullet->sprite.getGlobalBounds().intersects(shield->sprite.getGlobalBounds())) {
                //std::cout << "Collision detected!" << std::endl;
                shield->takeDamage(bullet->getDamage()); // ������ ����
                bullet->crashed(); // �Ѿ� ���� ����
            }
        }
        for (auto missile : missiles) {
            if (missile->sprite.getGlobalBounds().intersects(shield->sprite.getGlobalBounds())) {
                //std::cout << "Collision detected!" << std::endl;
                shield->takeDamage(missile->getDamage()); // ������ ����
                missile->crashed(); // �Ѿ� ���� ����

                if ((missile)->sprite.getGlobalBounds().intersects((shield)->sprite.getGlobalBounds())) { // �浹 �߻� ��

                    shield->takeDamage((missile)->getDamage());   // Enemy�� ü�� ����
                    (missile)->crashed();    // �̻��� �浹 ������ ���� ����
                    // ���� ����
                    sf::FloatRect boundsMissile = (missile)->sprite.getGlobalBounds();
                    sf::Vector2f explosionPosition(
                        boundsMissile.left + boundsMissile.width / 2,
                        boundsMissile.top + boundsMissile.height / 2
                    );
                    createExplosion(explosionPosition, ExplosionType::MissileImpact);
                }
            }
        }
        for (auto allyMissile : allyMissiles) {
            if (allyMissile->sprite.getGlobalBounds().intersects(shield->sprite.getGlobalBounds())) {
                //std::cout << "Collision detected!" << std::endl;
                shield->takeDamage(allyMissile->getDamage()); // ������ ����
                allyMissile->crashed(); // �Ѿ� ���� ����
            }
        }
    }
}


// ���� ����ü-�÷��̾� �浹 ó��
void Player::enemyProjectileCollision(std::vector<std::unique_ptr<Missile>>& globalMissiles, std::vector<Enemy*>& enemies) {
    for (auto enemyMissileIt = globalMissiles.begin(); enemyMissileIt != globalMissiles.end(); enemyMissileIt++) {
        if ((*enemyMissileIt)->checkCrashed()) continue;        // �̹� �浹�� �Ͼ�ٸ� continue
        bool misileDestroyed = false;
        if (*enemyMissileIt == nullptr) {  // nullptr üũ
            break;
        }

        // �÷��̾� Missile ó��   
        for (auto missileIt = missiles.begin(); missileIt != missiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr üũ
                break;
            }
            if ((*enemyMissileIt)->sprite.getGlobalBounds().intersects((*missileIt)->sprite.getGlobalBounds())) { // �浹 �߻� �� 
                misileDestroyed = true;
                (*missileIt)->crashed();    // �÷��̾� �̻��� �浹 ������ ���� ����
                sf::Vector2f playerMissilePostion = (*missileIt)->getPosition();

                for (auto enemyMissilTmpIt = globalMissiles.begin(); enemyMissilTmpIt != globalMissiles.end(); enemyMissilTmpIt++) {    // ���� �� ���� �̻��� ��˻�
                    sf::Vector2f enemyMissilePostion = (*enemyMissilTmpIt)->getPosition();
                    sf::Vector2f dist = playerMissilePostion - enemyMissilePostion;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                    createExplosion(playerMissilePostion, ExplosionType::MissileImpact);

                    if (distance < (*missileIt)->getRange()) {
                        (*enemyMissilTmpIt)->crashed();    // ���� �̻��� �浹 ������ ���� ����
                    }
                }

                // �Ʊ� �̻��� ���� �� ������ �ǰ�ó��

                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); 
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                sf::Vector2f missiletopcenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top);
                createExplosion(missiletopcenter, ExplosionType::MissileImpact);

                for (auto enemyTmpIt = enemies.begin(); enemyTmpIt != enemies.end(); enemyTmpIt++) {
                    if (*enemyTmpIt == nullptr) {  // nullptr üũ
                        break;
                    }
                    sf::FloatRect boundsTmpEnemy = (*enemyTmpIt)->sprite.getGlobalBounds();
                    sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);
                    sf::Vector2f dist = tmpEnemyCenter - missileCenter;
                    double distance = sqrt(dist.x * dist.x + dist.y * dist.y);

                    if (distance < (*missileIt)->getRange()) {

                        (*enemyTmpIt)->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����

                        if ((*enemyTmpIt)->getHealth() <= 0) {
                            createExplosion(tmpEnemyCenter, ExplosionType::EnemyDestroyed);
                        }
                    }

                }



            }
            if (misileDestroyed) break;
        }

        if (misileDestroyed) {
            continue; // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �̵�
        }

        // �ʻ�� Missile ó��   
        if (stageNumber != 2) {     // �ٴ� ���������� �ƴ� ���
            for (auto missileIt = allyMissiles.begin(); missileIt != allyMissiles.end(); missileIt++) {
                if (*missileIt == nullptr) {  // nullptr üũ
                    break;
                }
                if ((*missileIt)->sprite.getGlobalBounds().intersects((*enemyMissileIt)->sprite.getGlobalBounds())) { // �浹 �߻� ��
                    // sf::FloatRect boundsMissile = (*missileIt)->shape.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                    //sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);
                    ////sf::Vector2f enemyCenter = sf::Vector2f(boundsEnemy.left + boundsEnemy.width / 2, boundsEnemy.top + boundsEnemy.height / 2);
                    
                    sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds(); // , boundsEnemy = (*enemyIt)->sprite.getGlobalBounds();
                    sf::Vector2f missiletopcenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top);
                    createExplosion(missiletopcenter, ExplosionType::MissileImpact);

                    (*enemyMissileIt)->crashed();    // �̻��� �浹 ������ ���� ����
                    (*missileIt)->crashed();    // �̻��� �浹 ������ ���� ����
                    misileDestroyed = true;
                }
            }
            if (misileDestroyed) {
                continue; // Enemy�� �����Ǿ����Ƿ� ���� Enemy�� �̵�
            }
        }

        // �÷��̾�� �浹 ó��
        if ((*enemyMissileIt)->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds())) { // �浹 �߻� ��
            this->takeDamage(1.0f);
            this->changeHeartSprite();
            (*enemyMissileIt)->crashed();    // �̻��� �浹 ������ ���� ����
        }
    }
    deleteThisProjectile();

}
void Player::bossCollision(Boss* boss) {
        // �÷��̾��� ���ݰ� ���� �浹 ó��
        // Missile ó��   // �̻����� ������ �Ѿ˿� ���� ���� ���� ���� ������ ���� continue�� ���� �߻��� �� �־� �Ѿ˺��� �켱 �浹ó��
        for (auto missileIt = missiles.begin(); missileIt != missiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr üũ
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((boss)->sprite.getGlobalBounds())) { // �浹 �߻� ��

                boss->takeDamage((*missileIt)->getDamage());   // Enemy�� ü�� ����
                (*missileIt)->crashed();    // �̻��� �浹 ������ ���� ����
                // ���� ����
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds();
                sf::Vector2f explosionPosition(
                    boundsMissile.left + boundsMissile.width / 2,
                    boundsMissile.top + boundsMissile.height / 2
                );
                createExplosion(explosionPosition, ExplosionType::MissileImpact);


                //if ((boss)->getHealth() <= 0) {
                //    createExplosion(sf::Vector2f(450, 0), ExplosionType::Q_missileImpact);
                //    return;     // ���� �ϳ��� �˻��ϹǷ� ���� óġ �� �ٷ� return
                //}
            }
        }

        // Bullet ó��
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++) {
            if ((*bulletIt)->sprite.getGlobalBounds().intersects((boss)->sprite.getGlobalBounds())) { // �浹 �߻� ��

                (boss)->takeDamage((*bulletIt)->getDamage());   // Boss�� ü�� ����
                (*bulletIt)->crashed();
                //if ((boss)->getHealth() <= 0) {
                //    createExplosion(sf::Vector2f(450, 0), ExplosionType::Q_missileImpact);
                //    return;     // ���� �ϳ��� �˻��ϹǷ� ���� óġ �� �ٷ� return
                //}
            }
        }

        // �ʻ�� Missile ó��   
        for (auto missileIt = allyMissiles.begin(); missileIt != allyMissiles.end(); missileIt++) {
            if (*missileIt == nullptr) {  // nullptr üũ
                break;
            }
            if ((*missileIt)->sprite.getGlobalBounds().intersects((boss)->sprite.getGlobalBounds())) { // �浹 �߻� ��
                sf::FloatRect boundsMissile = (*missileIt)->sprite.getGlobalBounds();
                sf::Vector2f missileCenter = sf::Vector2f(boundsMissile.left + boundsMissile.width / 2, boundsMissile.top + boundsMissile.height / 2);


                sf::FloatRect boundsTmpEnemy = (boss)->sprite.getGlobalBounds();
                sf::Vector2f tmpEnemyCenter = sf::Vector2f(boundsTmpEnemy.left + boundsTmpEnemy.width / 2, boundsTmpEnemy.top + boundsTmpEnemy.height / 2);


                boss->takeDamage((*missileIt)->getDamage());   // Boss�� ü�� ����
                createExplosion(missileCenter, ExplosionType::EnemyDestroyed);
                (*missileIt)->crashed();    // �̻��� �浹 ������ ���� ����

           
            }
        }
        int flag = 0;
        // ���� ü���� 0 ������ ��� ���� ȿ�� ����
        //if (boss->getHealth() <= 0) {
        //    // ���� �ı� �� ū ���� ȿ�� ����
        //    createExplosion(sf::Vector2f(450, 0), ExplosionType::Q_missileImpact);     

        //
        //}

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

    // �Ѿ˰� �̻����� ���� ������Ʈ
    for (Bullet* bullet : bullets) {
        bullet->update(); // �߻�ü ���� ������Ʈ
    }
    for (Missile* missile : missiles) {
        missile->update(); // �߻�ü ���� ������Ʈ
    }

    // �Ʊ� ������ �߻�ü ������Ʈ
    for (Missile* allyMissile : allyMissiles) {
      /*  std::cout << allyMissile->sprite.getGlobalBounds().left << " " << allyMissile->sprite.getGlobalBounds().top << " "
            << allyMissile->sprite.getGlobalBounds().width << " " << allyMissile->sprite.getGlobalBounds().height << " " << std::endl;*/
        allyMissile->update();
    }

    //if (stageNumber == 2) {
    //    // �ʻ�� �߾ӿ��� �����ϸ� ���� ��ü ����
    //    if (std::any_of(allyMissiles.begin(), allyMissiles.end(), [](Missile* missile) {
    //        return missile->position.x >= WINDOWWIDTH / 2.0f + 100;
    //        })) {
    //        // ���� ��ü ����
    //        for (auto* enemy : enemies) {
    //            delete enemy;  // ���� �޸� ����
    //        }
    //        enemies.clear(); // ���� ���� �ʱ�ȭ
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

    // ȭ�� ������ ���� �߻�ü ����
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
        bullet->draw(window); // �߻�ü ���� ������Ʈ
        //  std::cout << "Drawing bullet at position: " << bullet->position.x << ", " << bullet->position.y << std::endl;

    }
    for (Missile* missile : missiles) {
        missile->draw(window); // �߻�ü ���� ������Ʈ
    }

    // �Ʊ� ������ �߻�ü �׸���
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
    if (!bulletTextures[2].loadFromFile("bullet_land.png") || !bulletTextures[3].loadFromFile("bullet_land.png")) {
        std::cerr << "Error loading bullet_land.png!" << std::endl;
    }
    if (!MissileTextures[0].loadFromFile("missile_sky.png")) {
        std::cerr << "Error loading bullet_sky.png!" << std::endl;
    }
    if (!MissileTextures[1].loadFromFile("missile_sea.png")) {
        std::cerr << "Error loading bullet_sea.png!" << std::endl;
    }
    if (!MissileTextures[2].loadFromFile("missile_land.png") || !MissileTextures[3].loadFromFile("missile_land.png")) {
        std::cerr << "Error loading bullet_land.png!" << std::endl;
    }
    if (!AllMissileTextures[0].loadFromFile("bullet_p_sky.png")) {
        std::cerr << "Error loading sky_missile.png!" << std::endl;
    }
    if (!AllMissileTextures[1].loadFromFile("Q_sea_missile.png")) {
        std::cerr << "Error loading Q_sea_missile.png!" << std::endl;
    }
    if (!AllMissileTextures[3].loadFromFile("Q_missile_land.png")) {
        std::cerr << "Error loading Q_missile_land.png!" << std::endl;
    }
}

//���� �ؽ�ó ������������ �ε�
void Player::loadExplosionTextures() {
    if (!enemyExplosionTextures[0].loadFromFile("explosion-3a.png")) {
        std::cerr << "Error loading explosion_enemy_stage1.png!" << std::endl;
    }
    if (!enemyExplosionTextures[1].loadFromFile("explosion-b.png")) {
        std::cerr << "Error loading explosion_enemy_stage2.png!" << std::endl;
    }
    if (!enemyExplosionTextures[2].loadFromFile("explosion-3a.png")) {
        std::cerr << "Error loading explosion_enemy_stage2.png!" << std::endl;
    }
    if (!enemyExplosionTextures[3].loadFromFile("explosion-3a.png")) {
        std::cerr << "Error loading explosion_enemy_boss.png!" << std::endl;
    }
    if (!missileExplosionTextures[0].loadFromFile("explosion-b.png")) {
        std::cerr << "Error loading explosion_missile_stage1.png!" << std::endl;
    }
    if (!missileExplosionTextures[1].loadFromFile("explosion.png")) {
        std::cerr << "Error loading explosion_missile_stage2.png!" << std::endl;
    }
    if (!missileExplosionTextures[2].loadFromFile("explosion.png") || !missileExplosionTextures[3].loadFromFile("explosion.png")) {
        std::cerr << "Error loading explosion_missile_stage2.png!" << std::endl;
    }
    if (!Q_missileExplosionTextures[1].loadFromFile("explosion_Q_sea.png")) {
        std::cerr << "Error loading explosion_missile_stage2.png!" << std::endl;
    }
    if (!Q_missileExplosionTextures[3].loadFromFile("explosion_Q_sea.png")) {
        std::cerr << "Error loading explosion_missile_stage2.png!" << std::endl;
    }
    if (!boExplosionTextures[3].loadFromFile("explosion-3a.png")) {
        std::cerr << "Error loading explosion_enemy_boss.png!" << std::endl;
    }

}

// ���� ����
void Player::createExplosion(sf::Vector2f position, ExplosionType type) {
    Explosion explosion;
    explosion.elapsedTime = 0.0f;
    explosion.frameTime = 0.1f; // �� ������ ���� �ð�
    explosion.currentFrame = 0;
    explosion.type = type;


    sf::Texture* texture = nullptr;

    // �ؽ�ó �� ���Ǻ� ó��
   // explosion.sprite.setTexture(getExplosionTexture(stageNumber - 1));

    if (type == ExplosionType::EnemyDestroyed) {
        texture = &enemyExplosionTextures[stageNumber - 1];
    }
    else if (type == ExplosionType::MissileImpact) {
        texture = &missileExplosionTextures[stageNumber - 1];
    }
    else if (type == ExplosionType::Q_missileImpact) {
        texture = &Q_missileExplosionTextures[stageNumber - 1];
    }
    else if (type == ExplosionType::bossu) {
        texture = &boExplosionTextures[stageNumber - 1];
    }
 

    if (texture != nullptr) {
        explosion.sprite.setTexture(*texture);

        // �ؽ�ó ũ��� ������ �� ���
        int textureWidth = texture->getSize().x;
        int frameWidth = 32; // �� �������� ���� ���� ũ��
        explosion.totalFrames = textureWidth / frameWidth; // ������ ���� ���

        //// ��������Ʈ ũ�� ����
        //if (type == ExplosionType::Q_missileImpact) {
        //    explosion.sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, 32));
        //    explosion.sprite.setScale(900.0f /texture->getSize().x, 900.0f /texture->getSize().y); // ȭ�� ��ü ä���
        //    explosion.sprite.setPosition(450.0f, 0.0f);

        //    explosions.push_back(explosion);
        //}
        //else if (type == ExplosionType::bossu) {
        //    explosion.sprite.setScale(5.0f, 5.0f); // bossu Ÿ�� ũ�� ����
        //    explosions.push_back(explosion);

        //}

        //else {
        //    explosion.sprite.setScale(2.5f, 2.5f); // �⺻ ũ�� ����

        //    explosion.sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, 32)); // ù ������
        //    explosion.sprite.setPosition(position);
        //    explosions.push_back(explosion);
        //}
                // ���� ũ�� ����
        if (type == ExplosionType::bossu) {
            explosion.sprite.setScale(5.0f, 5.0f); // ���� ���� ũ�� ����
        }
        else {
            explosion.sprite.setScale(2.5f, 2.5f); // �⺻ ũ�� ����
        }

        explosion.sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, 32)); // ù ������ ����
        explosion.sprite.setPosition(position);
        explosions.push_back(explosion);
    }

}

// ���� ������Ʈ
void Player::updateExplosions(float dt) {
    for (auto it = explosions.begin(); it != explosions.end();) {
        it->elapsedTime += dt;
        if (it->elapsedTime >= it->frameTime) {
            it->elapsedTime -= it->frameTime;
            it->currentFrame++;
            if (it->currentFrame >= it->totalFrames) {
                it = explosions.erase(it); // ���� �ִϸ��̼� ���� �� ���� 
                continue;
            }
            else {
                int frameWidth = 32; // �� �������� ���� ũ��
                int frameHeight = 32; // �� �������� ���� ũ��

              
                // ExplosionType�� ���� ũ�� ����
                if (it->type == ExplosionType::bossu) {
                    it->sprite.setTextureRect(sf::IntRect(it->currentFrame * frameWidth, 0, frameWidth, frameHeight));
                }
                else if (it->type == ExplosionType::MissileImpact || it->type == ExplosionType::EnemyDestroyed) {
                    it->sprite.setTextureRect(sf::IntRect(it->currentFrame * frameWidth, 0, frameWidth, frameHeight));

                }
                else {//������

                    it->sprite.setTextureRect(sf::IntRect(it->currentFrame * frameWidth, 0, frameWidth, frameHeight));
               
                    it->sprite.setScale(900.0f / frameWidth, 900.0f / frameHeight); // ȭ�� ��ü ũ�� ����
                }
            }
        }
        ++it;
    }

}

// ���� ������
void Player::renderExplosions(sf::RenderWindow& window) {
    for (const auto& explosion : explosions) {
        window.draw(explosion.sprite);
    }
}
void Player::clearExplosions() {
    explosions.clear();
}

void Player::clearProjectiles() {
    bullets.clear();    // �÷��̾��� �Ѿ� ����
    missiles.clear();   // �÷��̾��� �̻��� ����
    allyMissiles.clear(); // �Ʊ��� �̻��� ����
}
