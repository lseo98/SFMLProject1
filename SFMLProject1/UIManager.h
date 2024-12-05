#pragma once
#include <string>
#include <set>
#include <vector>
class UIManager {
public:
    UIManager();
    void init();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(int stageNumber, bool isGameOver);
    void render(sf::RenderWindow& window);
    void setBackground(int stageNumber);
    void drawGameOverScreen(sf::RenderWindow& window);
    bool isInputFocused() const;
    void setCooldownRatios(float ultimateRatio, float specialRatio);
    void updateKeyBoxes();
    sf::Texture texture_Q[3];
    sf::Texture texture_E[3];
    sf::Texture tkeybord;
    sf::Sprite sprite_Q[3];
    sf::Sprite sprite_E[3];
    sf::Sprite skeybord;
    std::set<sf::Keyboard::Key> activeKeys; // 현재 눌린 키들을 추적
    std::vector<sf::RectangleShape> additionalBoxes; // 눌린 키에 해당하는 박스들을 저장
    int currentStageNumber;

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text inputText;
    sf::Text text;
    sf::RectangleShape inputBoxl, inputBoxr, smallBoxr, coolbar_Q, coolbar_E, boxE, boxQ, boxdir, keyb;
    sf::Text skytext, seatext, landtext;
    sf::Text textbox;
    sf::Text gameOverText;
    sf::Text key, key2, QE;
    bool isInputActive;
    std::string userInput;
    std::string s2;
    // 쿨타임 비율 저장 멤버 변수 추가
    float ultimateCooldownRatio;
    float specialCooldownRatio;
    // 쿨타임 바를 그리기 위한 RectangleShape 멤버 변수
    sf::RectangleShape ultimateCooldownBar;
    sf::RectangleShape specialCooldownBar;
};