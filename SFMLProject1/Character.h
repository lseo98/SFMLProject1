#pragma once
#include <SFML/Graphics.hpp>

class Character {
public:
    Character();  
    Character(float health, float speed, sf::Vector2f position);
    virtual ~Character() = default;

    virtual void take_damage(float amount);
    virtual void draw(sf::RenderWindow& window);

    float get_health() const;
    float get_speed() const;

protected:
    float health;
    float speed;
    sf::Vector2f position;
    sf::RectangleShape shape;  // 그래픽 표현을 위한 SFML 도형
};
