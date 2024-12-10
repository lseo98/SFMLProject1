#pragma once
#include <string>
#include <set>
#include <vector>
#include "Player.h"
#include <functional>


class UIManager {
public:
    UIManager();
    void init();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(int stageNumber, bool isGameOver, Player& player);
    void render(sf::RenderWindow& window);
    void setBackground(int stageNumber);
    void drawGameOverScreen(sf::RenderWindow& window);
    bool isInputFocused() const;
    void setCooldownRatios(float ultimateRatio, float specialRatio);
    void updateKeyBoxes();
    void setStageChangeCallback(std::function<void(int)> callback);
    void setRestartCallback(std::function<void()> callback);
    sf::Texture texture_Q[4];
    sf::Texture texture_E[4];
    sf::Texture tkeybord;
    sf::Sprite sprite_Q[4];
    sf::Sprite sprite_E[4];
    sf::Sprite skeybord;
    std::set<sf::Keyboard::Key> activeKeys; // ���� ���� Ű���� ����
    std::vector<sf::RectangleShape> additionalBoxes; // ���� Ű�� �ش��ϴ� �ڽ����� ����
    int currentStageNumber;
    std::function<void(int)> onStageChange; // �������� ���� �ݹ�
    std::function<void()> onRestart; // restart �ݹ� �Լ�




    void updateMinigameInfo(int arr[3]); // �̴ϰ��� �����͸� ������Ʈ�ϴ� �޼���
    void renderMinigame(sf::RenderWindow& window);

    sf::Texture tminigame_background;
    sf::Sprite sminigame_background;

    int remainingKeys; // ���� Ű ��
    char inputKey; // �Էµ� Ű
    char targetKey; // ��ǥ Ű

    sf::Text remainingKeysText; // ���� Ű �ؽ�Ʈ
    sf::Text inputKeyText;      // �Էµ� Ű �ؽ�Ʈ
    sf::Text targetKeyText;     // ��ǥ Ű �ؽ�Ʈ
    sf::Text pressText;     // ��ǥ Ű �ؽ�Ʈ

    sf::RectangleShape keyBox;  // Ű ���� �ڽ�

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

    sf::Clock timer; // ������ �׵θ� �ð� ����
    bool isRed = false; // EŰ �������� ����

    sf::Text bossText;              // "BOSS" �ؽ�Ʈ
    sf::Clock bossTextTimer;        // �ؽ�Ʈ ǥ�� Ÿ�̸�
    bool showBossText = false;      // "BOSS" �ؽ�Ʈ ǥ�� ����
    bool bossTextDisplayed = false; // "BOSS" �ؽ�Ʈ �� ���� ǥ��



};