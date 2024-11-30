#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include <iostream>


// UIManager.cpp
UIManager::UIManager() : isInputActive(false), currentStageNumber(1) {
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
    smallBoxr.setPosition(1375, 200);
    smallBoxr.setFillColor(sf::Color::Black);
    smallBoxr.setOutlineColor(sf::Color::White);
    smallBoxr.setOutlineThickness(5);

    // �ؽ�Ʈ ����
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(5, 630);

    text.setFont(font);
    text.setString("Remaining Enemies");
    text.setCharacterSize(38);
    text.setFillColor(sf::Color::White);
    text.setPosition(1410, 210);

    skytext.setFont(font);
    skytext.setString("AIR FORCE");
    skytext.setCharacterSize(38);
    skytext.setFillColor(sf::Color(100, 100, 100, 250));
    skytext.setPosition(1410, 290);

    seatext.setFont(font);
    seatext.setString("NAVY");
    seatext.setCharacterSize(38);
    seatext.setFillColor(sf::Color(100, 100, 100, 250));
    seatext.setPosition(1410, 340);

    landtext.setFont(font);
    landtext.setString("ARMY");
    landtext.setCharacterSize(38);
    landtext.setFillColor(sf::Color(100, 100, 100, 250));
    landtext.setPosition(1410, 390);

    textbox.setFont(font);
    textbox.setString("Welcome to the\n<Biocommander-II> terminal.\n\n___________________________\n\n>System\n\nFrendly unit destroyed.\n\n>System\n\n*Warning\n\nMental power exhausted.\nThe interrogation begins.\n\n>System\nCommand request received.\n\nFrom friendly Navy.\nType switch to help.");
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
}

void UIManager::handleEvent(const sf::Event& event) {
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
            // ���� ó�� (�ʿ�� ����)
            userInput += "\n";
        }
        else if (event.text.unicode < 128) {
            // �Ϲ� ���� �Է�
            userInput += static_cast<char>(event.text.unicode);
        }
        inputText.setString(userInput);
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
}

void UIManager::render(sf::RenderWindow& window) {
    // UI ��� �׸��� �ڵ�
    // ...
    window.draw(inputBoxl);
    window.draw(inputBoxr);
    window.draw(smallBoxr);

    window.draw(inputText);
    window.draw(text);
    window.draw(skytext);
    window.draw(seatext);
    window.draw(landtext);
    window.draw(textbox);
}
// UIManager.cpp

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

