#pragma once
#include <SFML/Graphics.hpp>

class Character {
public:
    Character();  
    Character(float health, float speed, sf::Vector2f position);
    virtual ~Character() = default;

    virtual void takeDamage(float amount);
    virtual void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f postion); // ��ġ �ʱ�ȭ

    float getHealth() const;
    float getSpeed() const;


    void updateAttack();
    void renderAttack();

    void setTexture(const std::string& textureFile); // �ؽ�ó ���� �Լ�

protected:
    float health;
    float speed;
    sf::Vector2f position;
    //sf::RectangleShape shape;  // �׷��� ǥ���� ���� SFML ����

//private:
    int width;
    int height;
    int stageNumber;

    sf::Texture texture;  // ĳ������ �ؽ�ó
    sf::Sprite sprite;    // ĳ������ ��������Ʈ
};
