#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include "Game.h"
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
        std::cerr << "폰트 파일을 로드할 수 없습니다." << std::endl;
    }
    // 입력 상자 설정
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

    // 텍스트 설정
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(30, 730);

    text.setFont(font);
    text.setString("Kill Count");
    text.setCharacterSize(38);
    text.setFillColor(sf::Color::White);
    text.setPosition(1410, 120);

    skytext.setFont(font);
    skytext.setString("AIR FORCE     0 / 40");
    skytext.setCharacterSize(38);
    skytext.setFillColor(sf::Color(100, 100, 100, 250));
    skytext.setPosition(1410, 200);

    seatext.setFont(font);
    seatext.setString("NAVY          0 / 40");
    seatext.setCharacterSize(38);
    seatext.setFillColor(sf::Color(100, 100, 100, 250));
    seatext.setPosition(1410, 250);

    landtext.setFont(font);
    landtext.setString("ARMY          0 /  40");
    landtext.setCharacterSize(38);
    landtext.setFillColor(sf::Color(100, 100, 100, 250));
    landtext.setPosition(1410, 300);

    textbox.setFont(font);
    textbox.setString("Welcome to the\n<Biocommander-II> terminal.\n___________________________\n\n>System\n\nCommand request received.\n\n*Warning\nUse restart as a last resort\n\n>System\nMental power exhausted.\nThe interrogation begins.\n\n>System\nIf the E key is red, \nthe cooldown is reduced.\n\nType switch to help.\n\n>  [skymap]  [seamap]\n   [landmap]  [restart]\n\nTyping Here\n->");
    textbox.setCharacterSize(25);
    textbox.setFillColor(sf::Color::Yellow);
    textbox.setPosition(5, 5);

    // 게임 오버 텍스트 설정
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::White);

    // 화면 중앙에 위치시키기
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.width / 2, textRect.height / 2);
    gameOverText.setPosition(1800 / 2, 900 / 2);

    // Q 궁극기 쿨타임 바 초기화
    ultimateCooldownBar.setSize(sf::Vector2f(150.0f, 0));
    ultimateCooldownBar.setFillColor(sf::Color(50, 50, 50, 100));
    ultimateCooldownBar.setPosition(1410, 460);

    // E 특수 공격 쿨타임 바 초기화
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
    if (!texture_Q[3].loadFromFile("Q_land.png")) {
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
    if (!texture_E[3].loadFromFile("E_land.png")) {
        std::cerr << "Error loading bullet_land.png!" << std::endl;
    }

    //스테이지별 필살기 사진
    sprite_Q->setTexture(texture_Q[1]); // Q 텍스처 설정
    sprite_Q->setScale(150.0f / 930.0f, 150.0f / 930.0f);
    sprite_Q->setPosition(1410, 460);

    //스테이지별 미사일 사진
    sprite_E->setTexture(texture_Q[1]); // E  텍스처 설정
    sprite_E->setScale(150.0f / 930.0f, 150.0f / 930.0f);
    sprite_E->setPosition(1600, 460);

    //쿨타임 표시 불투명 네모
    boxQ.setSize(sf::Vector2f(150, 150));
    boxQ.setPosition(1410, 460);
    boxQ.setOutlineColor(sf::Color::Green);
    boxQ.setOutlineThickness(3);

    boxE.setSize(sf::Vector2f(150, 150));
    boxE.setPosition(1600, 460);
    boxE.setOutlineColor(sf::Color::Green);
    boxE.setOutlineThickness(3);

    // QE 텍스트 설정
    QE.setFont(font);
    QE.setString("(Q)             (E)");
    QE.setCharacterSize(24);
    QE.setFillColor(sf::Color::White);
    QE.setPosition(1470, 615);

    //키보드 이미지
    tkeybord.loadFromFile("kkeybord.png");
    skeybord.setTexture(tkeybord); // Q 텍스처 설정
    skeybord.setPosition(1375, 670);

    keyb.setSize(sf::Vector2f(400, 150));
    keyb.setPosition(1375, 670);
    keyb.setOutlineColor(sf::Color::Green);
    keyb.setOutlineThickness(3);

    // BOSS 텍스트 
    bossText.setFont(font);
    bossText.setString("BOSS");
    bossText.setCharacterSize(150);
    bossText.setFillColor(sf::Color::Red);
    bossText.setStyle(sf::Text::Bold);
    bossText.setPosition(770, 900 / 2-150);

    //미니게임 배경 이미지
    if(!tminigame_background.loadFromFile("minigame.png"))
    std::cerr << "Minigame texture could not be loaded!" << std::endl;
    sminigame_background.setTexture(tminigame_background); // Q 텍스처 설정
    sminigame_background.setPosition(450, 0);

    // 남은 키 텍스트 초기화
    remainingKeysText.setFont(font);
    remainingKeysText.setCharacterSize(50);
    remainingKeysText.setString("  Left Keys");
    remainingKeysText.setFillColor(sf::Color::Red);
    remainingKeysText.setPosition(1420, 800); // 위치 조정

    // 입력된 키 텍스트 초기화
    inputKeyText.setFont(font);
    inputKeyText.setString("");
    inputKeyText.setCharacterSize(38);
    inputKeyText.setFillColor(sf::Color::Yellow);
    inputKeyText.setPosition(5, 250);

    // 목표 키 텍스트 초기화
    targetKeyText.setFont(font);
    targetKeyText.setString("");
    targetKeyText.setCharacterSize(160);
    targetKeyText.setFillColor(sf::Color::Red);
    targetKeyText.setPosition(1530, 300);

    // 목표 키 텍스트 초기화
    pressText.setFont(font);
    pressText.setString("PRESS");
    pressText.setCharacterSize(50);
    pressText.setFillColor(sf::Color::Red);
    pressText.setPosition(1500, 530);

    // 키 강조 박스 초기화
    keyBox.setSize(sf::Vector2f(200, 200));
    keyBox.setFillColor(sf::Color(200,50,50,100));
    keyBox.setOutlineColor(sf::Color::Red);
    keyBox.setOutlineThickness(5);
    keyBox.setPosition(1470, 300);

    // 시간 박스
    timebox.setSize(sf::Vector2f(400, 150));
    timebox.setPosition(1375, 30);
    timebox.setFillColor(sf::Color::Black);
    timebox.setOutlineColor(sf::Color::Red);
    timebox.setOutlineThickness(5);

    // 카운트다운 텍스트 설정
    countdownText.setFont(font);
    countdownText.setCharacterSize(130);
    countdownText.setFillColor(sf::Color::Red);
    countdownText.setString("5");  // 초기 값
    countdownText.setPosition(1410, 20); // 오른쪽 위 위치

    // 결과 텍스트 초기화
    resultText.setFont(font);
    resultText.setCharacterSize(60);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(20, 600); // 화면 왼쪽 아래에 출력
    resultString = ""; // 초기 문자열은 비어 있음
}

void UIManager::handleEvent(const sf::Event& event, sf::RenderWindow& window) { 
    // 마우스 클릭 이벤트 처리
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

    // 키보드 입력 처리
    if (isInputActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') {
            // 백스페이스 처리
            if (!userInput.empty()) {
                userInput.pop_back();
            }
        }
        else if (event.text.unicode == '\r') {
            s2 = userInput;
            userInput = "";

            // 입력값에 따라 스테이지 번호 설정 
            if (s2 == "skymap") {
                onStageChange(1); // 스테이지 1로 변경
                Game::stageTransitionClock.restart();

            }
            else if (s2 == "seamap") {
                onStageChange(2); // 스테이지 1로 변경
                Game::stageTransitionClock.restart();

            }
            else if (s2 == "landmap") {
                onStageChange(3); // 스테이지 1로 변경
                //std::cout << "landmap = " << s2 << std::endl;

            }
            else if (s2 == "restart") {
                if (onRestart) onRestart(); // restart 콜백 호출
                Game::stageTransitionClock.restart();
            }

            else {
                //std::cout << "Invalid input: " << s2 << std::endl;
            }


            // std::cout << "s2 = " << s2 << std::endl;
        }
        else if (event.text.unicode < 128) {
            // 일반 문자 입력
            userInput += static_cast<char>(event.text.unicode);
        }
        inputText.setString(userInput);
    }

    if (!isInputActive) {
        if (event.type == sf::Event::KeyPressed) {
            activeKeys.insert(event.key.code); // 키가 눌리면 activeKeys에 추가
        }
        if (event.type == sf::Event::KeyReleased) {
            activeKeys.erase(event.key.code); // 키가 떼지면 activeKeys에서 제거
        }
    }
    // 눌린 키에 따라 박스 업데이트
    updateKeyBoxes();
}

void UIManager::updateKeyBoxes() {
    additionalBoxes.clear(); // 기존 박스 제거

    for (const auto& key : activeKeys) {
        sf::RectangleShape tempBox(sf::Vector2f(47, 45));
        tempBox.setFillColor(sf::Color(100, 100, 100, 200)); // 박스 색상

        if (key == sf::Keyboard::Q) {
            tempBox.setPosition(1386, 687); // Q 키 위치
        }
        else if (key == sf::Keyboard::E) {
            tempBox.setPosition(1386 + 139, 687); // E 키 위치
        }
        else if (key == sf::Keyboard::A) {
            tempBox.setPosition(1386, 687 + 71); // A 키 위치
        }
        else if (key == sf::Keyboard::D) {
            tempBox.setPosition(1386 + 139, 687 + 71); // D 키 위치
        }
        else if (key == sf::Keyboard::W) {
            tempBox.setPosition(1386 + 70, 687); // W 키 위치
        }
        else if (key == sf::Keyboard::S) {
            tempBox.setPosition(1386 + 70, 687 + 71); // S 키 위치
        }
        else if (key == sf::Keyboard::Left) {
            tempBox.setPosition(1386 + 139 + 77, 687 + 71); // Left Arrow
        }
        else if (key == sf::Keyboard::Right) {
            tempBox.setPosition(1386 + 139 + 77 + 120, 687 + 71); // Right Arrow
        }
        else if (key == sf::Keyboard::Up) {
            tempBox.setPosition(1386 + 139 + 77 + 60, 687); // Up Arrow
        }
        else if (key == sf::Keyboard::Down) {
            tempBox.setPosition(1386 + 139 + 77 + 60, 687 + 71); // Down Arrow
        }

        additionalBoxes.push_back(tempBox); // 박스 추가
    }
}



void UIManager::update(int stageNumber, bool isGameOver, Player& player) {
    // UI 요소 업데이트 코드
    if (currentStageNumber != stageNumber) {
        setBackground(stageNumber);
        currentStageNumber = stageNumber;
    }

    // 스테이지에 따른 텍스트 색상 업데이트
    skytext.setFillColor(sf::Color(100, 100, 100, 250));
    seatext.setFillColor(sf::Color(100, 100, 100, 250));
    landtext.setFillColor(sf::Color(100, 100, 100, 250));

    if (stageNumber == 1)
        skytext.setFillColor(sf::Color::White);
    else if (stageNumber == 2)
        seatext.setFillColor(sf::Color::White);
    else if (stageNumber == 3)
        landtext.setFillColor(sf::Color::White);

    if (stageNumber == 4 && !bossTextDisplayed) {
        showBossText = true;       // 텍스트 표시 활성화
        bossTextDisplayed = true; // 텍스트가 이미 표시되었음 기록
        bossTextTimer.restart();  // 타이머 초기화
    }

    // 2초 후 BOSS 텍스트 숨기기
    if (showBossText && bossTextTimer.getElapsedTime().asSeconds() > 2.0f) {
        showBossText = false;      // 텍스트 표시 비활성화
    }

    sprite_Q->setTexture(texture_Q[stageNumber - 1]); // 텍스처 설정
    sprite_E->setTexture(texture_E[stageNumber - 1]); // 텍스처 설정

    skytext.setString("AIR FORCE  " + std::to_string(player.killCountEliteUnit1) + " / " + std::to_string(player.maxKillEliteCount));
    seatext.setString("NAVY       " + std::to_string(player.killCountEliteUnit2) + " / " + std::to_string(player.maxKillEliteCount));

    landtext.setString("ARMY       " + std::to_string(player.killCountEliteUnit3) + " / " + std::to_string(player.maxKillEliteCount));

    // 노말유닛 10마리 처치시 E키 빨간색으로 변환
    if (player.killCountNomalUnit == 10 && !isRed) {
        boxE.setOutlineColor(sf::Color::Red);
        isRed = true;
        player.setSpecialAttackCooldown(0.2);
        timer.restart();
    }
    // 3초가 지나면 테두리 색상을 원래대로 복구
    if (isRed && timer.getElapsedTime().asSeconds() > 3) {
        boxE.setOutlineColor(sf::Color::Green); // 기본 색상으로 복구
        isRed = false; // 강조 상태 해제
        player.killCountNomalUnit = 0; // 노말 유닛 처치 수 0으로 초기화
        player.setSpecialAttackCooldown(2);
    }
}

void UIManager::render(sf::RenderWindow& window) {

    float ultimateBarHeight = 150.0f * (ultimateCooldownRatio);
    ultimateCooldownBar.setSize(sf::Vector2f(150.0f, ultimateBarHeight));
    //std::cout << ultimateBarHeight << std::endl;

    float specialBarHeight = 150.0f * (specialCooldownRatio);
    specialCooldownBar.setSize(sf::Vector2f(150.0f, specialBarHeight));

    if (currentStageNumber == 5) {
        renderMinigame(window);
    }
    else {
        window.draw(inputBoxl);
        window.draw(inputBoxr);
        window.draw(smallBoxr);

        window.draw(inputText);
        window.draw(text);
      //
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

        // activeKeys에 있는 모든 박스 그리기
        for (const auto& box : additionalBoxes) {
            window.draw(box);
        }
        window.draw(QE);

        // 쿨타임 바 그리기
        window.draw(ultimateCooldownBar);
        window.draw(specialCooldownBar);

        // "BOSS" 텍스트 그리기
        if (showBossText) {
            window.draw(bossText);
        }
    }
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
//    // 체력바의 길이 계산
//    float maxHealth = dynamic_cast<EliteUnit*>(this) ? 300.0f : 100.0f; // 엘리트 유닛: 300, 일반 유닛: 100
//    float healthBarWidth = (this->getHealth() / maxHealth) * 96.0f; // 체력에 비례한 길이
//
//    // 체력바 (빨간색)
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
    case 4:
        backgroundImagePath = "land.png";
        break;
    //case 5:
    //    backgroundImagePath = "minigame.png";

    default:
        //std::cout << "background" << std::endl;
        break;
    }

    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        std::cerr << "배경 이미지를 로드할 수 없습니다: " << backgroundImagePath << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void UIManager::drawGameOverScreen(sf::RenderWindow& window) {
    window.draw(gameOverText);
}
bool UIManager::isInputFocused() const {
    return isInputActive;
}
void UIManager::setStageChangeCallback(std::function<void(int)> callback) {
    onStageChange = callback; // 콜백 저장
}
void UIManager::setRestartCallback(std::function<void()> callback) {
    onRestart = callback;
}



void UIManager::updateMinigameInfo(int arr[3], int countdownValue) {
    // 텍스트 업데이트
    remainingKeysText.setString(std::to_string(arr[0])+" Left Keys");
    inputKeyText.setString(std::to_string(arr[1]));
    targetKeyText.setString(std::to_string(arr[2]));

    // 결과 텍스트 갱신
    if (inputKeyText.getString() == targetKeyText.getString()) {
        resultString= inputKeyText.getString() + "\nCorrect!\n";  // 일치한 경우 누적
    }
    else {
        resultString = inputKeyText.getString() + "\nNo!\n";  // 불일치한 경우 누적
    }
    resultText.setString(resultString); // 결과 텍스트 업데이트

    // 카운트다운 업데이트
    countdownText.setString("00:0" + std::to_string(countdownValue));

    //if (countdownClock.getElapsedTime().asSeconds() >= 1.0f) {
    //    if (countdownValue > 0) {
    //        countdownValue--;  // 1초마다 감소
    //    }
    //    countdownText.setString("00:0" + std::to_string(countdownValue));
    //    countdownClock.restart();  // 타이머 리셋
    //}

    // 카운트다운이 0이 되었을 때
    if (countdownValue == 0) {
        isGameOver = true; // 게임 오버 상태 설정
    }
}
void UIManager::renderMinigame(sf::RenderWindow& window) {
    // 텍스트 렌더링
    window.draw(sminigame_background);
    window.draw(pressText);
    window.draw(remainingKeysText);
   // window.draw(inputKeyText);
    window.draw(targetKeyText);
    window.draw(timebox);
    window.draw(countdownText);
    window.draw(resultText);




    // 키 강조 박스
    window.draw(keyBox);
    // 게임 오버 상태면 게임 오버 화면 표시
    if (isGameOver) {
        drawGameOverScreen(window);
    }
}





