#pragma once
#include <SFML/Graphics.hpp>

class Character {
public:
    Character();  
    Character(float health, float speed, sf::Vector2f position);
    virtual ~Character() = default;

    virtual void take_damage(float amount);
    virtual void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f postion); // 위치 초기화

    float get_health() const;
    float get_speed() const;

    void updateAttack();
    void renderAttack();

protected:
    float health;
    float speed;
    sf::Vector2f position;
    sf::RectangleShape shape;  // 그래픽 표현을 위한 SFML 도형

//private:
    int width;
    int height;
    int stageNumber;
};
