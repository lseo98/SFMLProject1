//#pragma once
//#include "PlayerAttack.h"
//#include "Projectile.h"
//#include <vector>
//#include <memory>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//class SkyPlayerAttack : public PlayerAttack {
//public:
//    SkyPlayerAttack() = default;
//
//    void basic_attack(const sf::Vector2f& playerPosition) override;
//    void special_attack(const sf::Vector2f& playerPosition) override;
//    void ultimate_attack() override;
//    void updateProjectiles();
//    void drawProjectiles(sf::RenderWindow& window);
//
//private:
//    std::vector<std::unique_ptr<Projectile>> projectiles; // �߻�ü���� �����ϴ� ����
//};
//
//#include "SkyPlayerAttack.h"
////#include "Bullet.h"
////#include "Missile.h"
////
////extern int WINDOWWIDTH, WINDOWHEIGHT;
////
////// �⺻ ���� ����: �Ѿ��� �����Ͽ� �������� �߻�
////void SkyPlayerAttack::basic_attack(const sf::Vector2f& playerPosition) {
////    std::cout << "Sky Stage: �⺻ ���� - �Ѿ� �߻�\n";
////    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, sf::Vector2f(0.0f, -1.0f))); // �������� �߻�
////}
////
////// Ư�� ���� ����: ���� �̻��� ����
////void SkyPlayerAttack::special_attack(const sf::Vector2f& playerPosition) {
////    std::cout << "Sky Stage: Ư�� ���� - ���� �̻��� �߻�\n";
////    projectiles.emplace_back(std::make_unique<Missile>(playerPosition)); // ���� �̻��� ����
////}
////
////// �ʻ�� (����� ���� ����)
////void SkyPlayerAttack::ultimate_attack() {
////    std::cout << "Sky Stage: �ʻ�� - �Ʊ� ����� ���� ����\n";
////    // �ʻ�� ���� �߰� ����
////}
////
////void SkyPlayerAttack::updateProjectiles() {
////
////    for (auto& projectile : projectiles) {
////        projectile->update(); // �߻�ü ���� ������Ʈ
////    }
////
////    projectiles.erase(
////        std::remove_if(projectiles.begin(), projectiles.end(),
////            [](const std::unique_ptr<Projectile>& projectile) {
////                return projectile->isOffScreen(); // ȭ�� ũ�⸦ ���
////            }),
////        projectiles.end());
////
////}
////
////void SkyPlayerAttack::drawProjectiles(sf::RenderWindow& window) {
////    for (auto& projectile : projectiles) {
////        projectile->draw(window); // �߻�ü ȭ�鿡 �׸���
////    }
////}