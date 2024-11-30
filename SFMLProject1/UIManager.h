#pragma once
#include <string>

class UIManager {
public:
    UIManager();
    void init();
    void handleEvent(const sf::Event& event);
    void update(int stageNumber, bool isGameOver);
    void render(sf::RenderWindow& window);
    void setBackground(int stageNumber);
    void drawGameOverScreen(sf::RenderWindow& window);
    bool isInputFocused() const;

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text inputText;
    sf::Text text;
    sf::RectangleShape inputBoxl, inputBoxr, smallBoxr;
    sf::Text skytext, seatext, landtext;
    sf::Text textbox;
    sf::Text gameOverText;
    bool isInputActive;
    std::string userInput;
    int currentStageNumber;

};
