#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include <iostream>
#include <vector>

// UIManager.cpp
UIManager::UIManager() : isInputActive(false), currentStageNumber(1),
ultimateCooldownRatio(0.0f), specialCooldownRatio(0.0f) {
    init();
}

void UIManager::init() {
    int stageNumber = 1;
    if (!font.loadFromFile("R2.ttc")) {
        std::cerr << "��Ʈ ������ �ε��� �� �����ϴ�." << std::endl;
    }
    // �Է� ���� ����
    inputBoxl.setSize(sf::Vector2f(450, 900));
    inputBoxl.setPosition(0, 0);
    inputBoxl.setFillColor(sf::Color::Black);
    inputBoxl.setOutlineColor(sf::Color::Green);
    inputBoxl.setOutlineThickness(2);

    inputBoxr.setSize(sf::Vector2f(450, 900));
    inputBoxr.setPosition(1350, 0);
    inputBoxr.setFillColor(sf::Color::Black);
    inputBoxr.setOutlineColor(sf::Color::Green);
    inputBoxr.setOutlineThickness(2);

    smallBoxr.setSize(sf::Vector2f(400, 300));
    smallBoxr.setPosition(1375, 110);
    smallBoxr.setFillColor(sf::Color::Black);
    smallBoxr.setOutlineColor(sf::Color::White);
    smallBoxr.setOutlineThickness(5);

    // �ؽ�Ʈ ����
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(30, 730);

    text.setFont(font);
    text.setString("Remaining Enemies");
    text.setCharacterSize(38);
    text.setFillColor(sf::Color::White);
    text.setPosition(1410, 120);

    skytext.setFont(font);
    skytext.setString("AIR FORCE");
    skytext.setCharacterSize(38);
    skytext.setFillColor(sf::Color(100, 100, 100, 250));
    skytext.setPosition(1410, 200);

    seatext.setFont(font);
    seatext.setString("NAVY");
    seatext.setCharacterSize(38);
    seatext.setFillColor(sf::Color(100, 100, 100, 250));
    seatext.setPosition(1410, 250);

    landtext.setFont(font);
    landtext.setString("ARMY");
    landtext.setCharacterSize(38);
    landtext.setFillColor(sf::Color(100, 100, 100, 250));
    landtext.setPosition(1410, 300);

    textbox.setFont(font);
    textbox.setString("Welcome to the\n<Biocommander-II> terminal.\n\n___________________________\n\n>System\n\nFrendly unit destroyed.\n\n>System\n\n*Warning\n\nMental power exhausted.\nThe interrogation begins.\n\n>System\nCommand request received.\n\nFrom friendly Navy.\nType switch to help.\n\n>[skymap]  [seamap]  [landmap]\n\nTyping Here\n->");
    textbox.setCharacterSize(25);
    textbox.setFillColor(sf::Color::Yellow);
    textbox.setPosition(5, 5);

    // ���� ���� �ؽ�Ʈ ����
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::White);

    // ȭ�� �߾ӿ� ��ġ��Ű��
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.width / 2, textRect.height / 2);
    gameOverText.setPosition(1800 / 2, 900 / 2);

    // Q �ñر� ��Ÿ�� �� �ʱ�ȭ
    ultimateCooldownBar.setSize(sf::Vector2f(150.0f, 0));
    ultimateCooldownBar.setFillColor(sf::Color(50, 50, 50, 100));
    ultimateCooldownBar.setPosition(1410, 460);

    // E Ư�� ���� ��Ÿ�� �� �ʱ�ȭ
    specialCooldownBar.setSize(sf::Vector2f(150.0f, 0));
    specialCooldownBar.setFillColor(sf::Color(50, 50, 50, 100)); 
    specialCooldownBar.setPosition(1600, 460);

    if (!texture_Q[0].loadFromFile("Q_sky.png")) {
        std::cerr << "Error loading bullet_sky.png!" << std::endl;
    }
    if (!texture_Q[1].loadFromFile("Q_sea.png")) {
        std::cerr << "Error loading bullet_sea.png!" << std::endl;
    }
    if (!texture_Q[2].loadFromFile("Q_land.png")) {
        std::cerr << "Error loading bullet_land.png!" << std::endl;
    }
    if (!texture_E[0].loadFromFile("E_sky.png")) {
        std::cerr << "Error loading bullet_sky.png!" << std::endl;
    }
    if (!texture_E[1].loadFromFile("E_sea.png")) {
        std::cerr << "Error loading bullet_sea.png!" << std::endl;
    }
    if (!texture_E[2].loadFromFile("E_land.png")) {
        std::cerr << "Error loading bullet_land.png!" << std::endl;
    }

    //���������� �ʻ�� ����
    sprite_Q->setTexture(texture_Q[1]); // Q �ؽ�ó ����
    sprite_Q->setScale(150.0f/930.0f, 150.0f / 930.0f);
    sprite_Q->setPosition(1410, 460);

    //���������� �̻��� ����
    sprite_E->setTexture(texture_Q[1]); // E  �ؽ�ó ����
    sprite_E->setScale(150.0f / 930.0f, 150.0f / 930.0f);
    sprite_E->setPosition(1600, 460);

    //��Ÿ�� ǥ�� ������ �׸�
    boxQ.setSize(sf::Vector2f(150, 150));
    boxQ.setPosition(1410, 460);
    boxQ.setOutlineColor(sf::Color::Green);
    boxQ.setOutlineThickness(3);

    boxE.setSize(sf::Vector2f(150, 150));
    boxE.setPosition(1600, 460);
    boxE.setOutlineColor(sf::Color::Green);
    boxE.setOutlineThickness(3);

    // QE �ؽ�Ʈ ����
    QE.setFont(font);
    QE.setString("(Q)             (E)");
    QE.setCharacterSize(24);
    QE.setFillColor(sf::Color::White);
    QE.setPosition(1470, 615);

    //Ű���� �̹���
    tkeybord.loadFromFile("kkeybord.png");
    skeybord.setTexture(tkeybord); // Q �ؽ�ó ����
    skeybord.setPosition(1375,670);

    keyb.setSize(sf::Vector2f(400, 150));
    keyb.setPosition(1375, 670);
    keyb.setOutlineColor(sf::Color::Green);
    keyb.setOutlineThickness(3);


    //// keybord �ؽ�Ʈ ����
    //key.setFont(font);
    //key.setString("Q     W     E             ��");
    //key.setCharacterSize(24);
    //key.setFillColor(sf::Color::Black);
    //key.setPosition(1399, 693);

    //key2.setFont(font);
    //key2.setString("A     S     D             ��     ��     ��");
    //key2.setCharacterSize(24);
    //key2.setFillColor(sf::Color::Black);
    //key2.setPosition(1399, 763);
    //


}

void UIManager::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    // ���콺 Ŭ�� �̺�Ʈ ó��
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (inputBoxl.getGlobalBounds().contains(mousePos) ||
                inputBoxr.getGlobalBounds().contains(mousePos)) {
                isInputActive = true;
            }
            else {
                isInputActive = false;
            }
        }
    }

    // Ű���� �Է� ó��
    if (isInputActive && event.type == sf::Event::TextEntered) {      
        if (event.text.unicode == '\b') {
            // �齺���̽� ó��
            if (!userInput.empty()) {
                userInput.pop_back();
            }
        }
        else if (event.text.unicode == '\r') {  
            s2=userInput;
            userInput = "";
            
            // �Է°��� ���� �������� ��ȣ ���� 
            if (s2 == "skymap") {
                currentStageNumber = 1;
                
            }
            else if (s2 == "seamap") {
                currentStageNumber = 2;
            }
            else if (s2 == "landmap") {
                currentStageNumber = 3;
                std::cout << "landmap = " << s2 << std::endl;

            }
            else {
                std::cout << "Invalid input: " << s2 << std::endl;
            }

           // std::cout << "s2 = " << s2 << std::endl;
        }
        else if (event.text.unicode < 128) {
            // �Ϲ� ���� �Է�
            userInput += static_cast<char>(event.text.unicode);
        }
        inputText.setString(userInput);
    }

    if (!isInputActive) {
        if (event.type == sf::Event::KeyPressed) {
            activeKeys.insert(event.key.code); // Ű�� ������ activeKeys�� �߰�
        }
        if (event.type == sf::Event::KeyReleased) {
            activeKeys.erase(event.key.code); // Ű�� ������ activeKeys���� ����
        }
    }
    // ���� Ű�� ���� �ڽ� ������Ʈ
    updateKeyBoxes();
}
//1375 670
//11 17ad
//71 72
void UIManager::updateKeyBoxes() {
    additionalBoxes.clear(); // ���� �ڽ� ����

    for (const auto& key : activeKeys) {
        sf::RectangleShape tempBox(sf::Vector2f(47, 45));
        tempBox.setFillColor(sf::Color(100, 100, 100, 200)); // �ڽ� ����

        if (key == sf::Keyboard::Q) {
            tempBox.setPosition(1386,687); // Q Ű ��ġ
        }
        else if (key == sf::Keyboard::E) {
            tempBox.setPosition(1386+139, 687); // E Ű ��ġ
        }
        else if (key == sf::Keyboard::A) {
            tempBox.setPosition(1386, 687+71); // A Ű ��ġ
        }
        else if (key == sf::Keyboard::D) {
            tempBox.setPosition(1386 + 139, 687+71); // D Ű ��ġ
        }
        else if (key == sf::Keyboard::W) {
            tempBox.setPosition(1386+70,687); // W Ű ��ġ
        }
        else if (key == sf::Keyboard::S) {
            tempBox.setPosition(1386 + 70, 687+71); // S Ű ��ġ
        }
        else if (key == sf::Keyboard::Left) {
            tempBox.setPosition(1386 + 139+77, 687 + 71); // Left Arrow
        }
        else if (key == sf::Keyboard::Right) {
            tempBox.setPosition(1386 + 139 + 77+120, 687 + 71); // Right Arrow
        }
        else if (key == sf::Keyboard::Up) {
            tempBox.setPosition(1386 + 139 + 77+60, 687); // Up Arrow
        }
        else if (key == sf::Keyboard::Down) {
            tempBox.setPosition(1386 + 139 + 77+60, 687 + 71); // Down Arrow
        }

        additionalBoxes.push_back(tempBox); // �ڽ� �߰�
    }
}


void UIManager::update(int stageNumber, bool isGameOver) {
    // UI ��� ������Ʈ �ڵ�
    // ...
    if (currentStageNumber != stageNumber) {
        setBackground(stageNumber);
        currentStageNumber = stageNumber;
    }

       // ���������� ���� �ؽ�Ʈ ���� ������Ʈ
    skytext.setFillColor(sf::Color(100, 100, 100, 250));
    seatext.setFillColor(sf::Color(100, 100, 100, 250));
    landtext.setFillColor(sf::Color(100, 100, 100, 250));

    if (stageNumber == 1)
        skytext.setFillColor(sf::Color::White);
    else if (stageNumber == 2)
        seatext.setFillColor(sf::Color::White);
    else if (stageNumber == 3)
        landtext.setFillColor(sf::Color::White);

     sprite_Q->setTexture(texture_Q[stageNumber - 1]); // �ؽ�ó ����
     sprite_E->setTexture(texture_E[stageNumber - 1]); // �ؽ�ó ����

}

void UIManager::render(sf::RenderWindow& window) {
    // UI ��� �׸��� �ڵ�
    // ...
        // ��Ÿ�� �� ũ�� ������Ʈ
    float ultimateBarHeight = 150.0f * (ultimateCooldownRatio);
    ultimateCooldownBar.setSize(sf::Vector2f(150.0f, ultimateBarHeight));
    //std::cout << ultimateBarHeight << std::endl;

    float specialBarHeight = 150.0f * (specialCooldownRatio);
    specialCooldownBar.setSize(sf::Vector2f(150.0f, specialBarHeight));   

    window.draw(inputBoxl);
    window.draw(inputBoxr);
    window.draw(smallBoxr);

    window.draw(inputText);
    window.draw(text);
    window.draw(skytext);
    window.draw(seatext);
    window.draw(landtext);
    window.draw(textbox); 
    window.draw(boxE);
    window.draw(boxQ);
 //   window.draw(keyb);
    window.draw(*sprite_Q);
    window.draw(*sprite_E);
    window.draw(skeybord);

    // activeKeys�� �ִ� ��� �ڽ� �׸���
    for (const auto& box : additionalBoxes) {
        window.draw(box);
    }
   window.draw(QE);

    // ��Ÿ�� �� �׸���
    window.draw(ultimateCooldownBar);
    window.draw(specialCooldownBar);
}
void UIManager::setCooldownRatios(float ultimateRatio, float specialRatio) {
    ultimateCooldownRatio = ultimateRatio;
    specialCooldownRatio = specialRatio;
}

//void Enemy::draw(sf::RenderWindow& window) {
//    this->sprite.setPosition(this->position);
//    window.draw(this->sprite);
//
//    sf::RectangleShape rectangle(sf::Vector2f(100.0f, 13.0f));
//    rectangle.setFillColor(sf::Color::White);
//    rectangle.setPosition(this->position.x, this->position.y - 10.0f);
//    window.draw(rectangle);
//
//
//    // ü�¹��� ���� ���
//    float maxHealth = dynamic_cast<EliteUnit*>(this) ? 300.0f : 100.0f; // ����Ʈ ����: 300, �Ϲ� ����: 100
//    float healthBarWidth = (this->getHealth() / maxHealth) * 96.0f; // ü�¿� ����� ����
//
//    // ü�¹� (������)
//    sf::RectangleShape healthBar(sf::Vector2f(healthBarWidth + 2, 11.0f));
//    healthBar.setFillColor(sf::Color::Red);
//    healthBar.setPosition(this->position.x + 1, this->position.y - 9.0f);
//    window.draw(healthBar);
//
//}
void UIManager::setBackground(int stageNumber) {
    std::string backgroundImagePath;
    switch (stageNumber) {
    case 1:
        backgroundImagePath = "sky.png";
        break;
    case 2:
        backgroundImagePath = "sea.png";
        break;
    case 3:
        backgroundImagePath = "land.png";
        break;
    default:
        std::cout << "background" << std::endl;
        break;
    }

    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        std::cerr << "��� �̹����� �ε��� �� �����ϴ�: " << backgroundImagePath << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void UIManager::drawGameOverScreen(sf::RenderWindow& window) {
    window.draw(gameOverText);
}
bool UIManager::isInputFocused() const {
    return isInputActive;
}