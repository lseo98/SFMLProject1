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

    void setTexture(const std::string& textureFile); // 텍스처 설정 함수

protected:
    float health;
    float speed;
    sf::Vector2f position;

    sf::Texture texture;  // 캐릭터의 텍스처
    sf::Sprite sprite;    // 캐릭터의 스프라이트
};
