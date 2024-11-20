#pragma once
#include <SFML/Graphics.hpp>

class Character {
public:
    Character();  
    Character(float health, float speed, sf::Vector2f position);
    virtual ~Character() = default;

    virtual void take_damage(float amount);
    virtual void draw(sf::RenderWindow& window);
    virtual void setPlayer(int stageNumber, std::string textureFile);

    float get_health() const;
    float get_speed() const;

    void updateAttack();
    void renderAttack();

protected:
    float health;
    float speed;
    sf::Vector2f position;
    sf::RectangleShape shape;  // 그래픽 표현을 위한 SFML 도형

private:
    int width;
    int height;
    int stageNumber;
};
