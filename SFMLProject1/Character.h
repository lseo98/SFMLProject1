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

    void setTexture(const std::string& textureFile); // �ؽ�ó ���� �Լ�

protected:
    float health;
    float speed;
    sf::Vector2f position;

    sf::Texture texture;  // ĳ������ �ؽ�ó
    sf::Sprite sprite;    // ĳ������ ��������Ʈ
};
