//#pragma once
//#include "Projectile.h"
//
//class Torpedo : public Projectile {
//public:
//    Torpedo(const sf::Vector2f& startPosition);
//
//    void update() override;
//    void draw(sf::RenderWindow& window) override;
//};

//#include "SkyPlayerAttack.h"
//#include "Bullet.h"
//#include "Missile.h"
//
//extern int WINDOWWIDTH, WINDOWHEIGHT;
//
//// �⺻ ���� ����: �Ѿ��� �����Ͽ� �������� �߻�
//void SkyPlayerAttack::basic_attack(const sf::Vector2f& playerPosition) {
//    std::cout << "Sky Stage: �⺻ ���� - �Ѿ� �߻�\n";
//    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, sf::Vector2f(0.0f, -1.0f))); // �������� �߻�
//}
//
//// Ư�� ���� ����: ���� �̻��� ����
//void SkyPlayerAttack::special_attack(const sf::Vector2f& playerPosition) {
//    std::cout << "Sky Stage: Ư�� ���� - ���� �̻��� �߻�\n";
//    projectiles.emplace_back(std::make_unique<Missile>(playerPosition)); // ���� �̻��� ����
//}
//
//// �ʻ�� (����� ���� ����)
//void SkyPlayerAttack::ultimate_attack() {
//    std::cout << "Sky Stage: �ʻ�� - �Ʊ� ����� ���� ����\n";
//    // �ʻ�� ���� �߰� ����
//}
//
//void SkyPlayerAttack::updateProjectiles() {
//
//    for (auto& projectile : projectiles) {
//        projectile->update(); // �߻�ü ���� ������Ʈ
//    }
//
//    projectiles.erase(
//        std::remove_if(projectiles.begin(), projectiles.end(),
//            [](const std::unique_ptr<Projectile>& projectile) {
//                return projectile->isOffScreen(); // ȭ�� ũ�⸦ ���
//            }),
//        projectiles.end());
//
//}
//
//void SkyPlayerAttack::drawProjectiles(sf::RenderWindow& window) {
//    for (auto& projectile : projectiles) {
//        projectile->draw(window); // �߻�ü ȭ�鿡 �׸���
//    }
//}