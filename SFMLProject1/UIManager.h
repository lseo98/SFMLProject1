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
    std::set<sf::Keyboard::Key> activeKeys; // ���� ���� Ű���� ����
    std::vector<sf::RectangleShape> additionalBoxes; // ���� Ű�� �ش��ϴ� �ڽ����� ����
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
    // ��Ÿ�� ���� ���� ��� ���� �߰�
    float ultimateCooldownRatio;
    float specialCooldownRatio;
    // ��Ÿ�� �ٸ� �׸��� ���� RectangleShape ��� ����
    sf::RectangleShape ultimateCooldownBar;
    sf::RectangleShape specialCooldownBar;
};