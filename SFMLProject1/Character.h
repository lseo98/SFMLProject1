#pragma once
#include <SFML/Graphics.hpp>

class Character {
public:
    Character();  
    Character(float health, float speed, sf::Vector2f position);
    virtual ~Character() = default;

    virtual void takeDamage(float amount);
    virtual void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f postion); // 위치 초기화

    float getHealth() const;
    float getSpeed() const;


    void updateAttack();
    void renderAttack();

    void setTexture(const std::string& textureFile); // 텍스처 설정 함수

protected:
    float health;
    float speed;
    sf::Vector2f position;
    //sf::RectangleShape shape;  // 그래픽 표현을 위한 SFML 도형

//private:
    int width;
    int height;
    int stageNumber;

    sf::Texture texture;  // 캐릭터의 텍스처
    sf::Sprite sprite;    // 캐릭터의 스프라이트
};
