//#pragma once
//#include "Projectile.h"
//#include <SFML/Graphics.hpp>
//
//class AntiTankMissile : public Projectile {
//public:
//    AntiTankMissile(const sf::Vector2f& startPosition);
//
//    void update() override;
//    void draw(sf::RenderWindow& window) override;
//};

//#include "AntiTankMissile.h"
//
//AntiTankMissile::AntiTankMissile(const sf::Vector2f& startPosition)
//    : Projectile(startPosition, sf::Vector2f(0.0f, -1.0f), 8.0f) { // 위쪽 방향, 속도 8.0f
//    shape.setRadius(10.0f);            // 미사일 크기 설정
//    shape.setFillColor(sf::Color::Yellow); // 미사일 색상 설정
//    shape.setPosition(position);        // 시작 위치 설정
//}
//
//void AntiTankMissile::update() {
//    adjustDirection();
//    position += direction * speed;
//    shape.setPosition(position); // 위치 업데이트
//}
//
//void AntiTankMissile::draw(sf::RenderWindow& window) {
//    window.draw(shape); // 창에 그리기
//}
