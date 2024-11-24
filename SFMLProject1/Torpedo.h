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
//// 기본 공격 구현: 총알을 생성하여 위쪽으로 발사
//void SkyPlayerAttack::basic_attack(const sf::Vector2f& playerPosition) {
//    std::cout << "Sky Stage: 기본 공격 - 총알 발사\n";
//    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, sf::Vector2f(0.0f, -1.0f))); // 위쪽으로 발사
//}
//
//// 특수 공격 구현: 유도 미사일 생성
//void SkyPlayerAttack::special_attack(const sf::Vector2f& playerPosition) {
//    std::cout << "Sky Stage: 특수 공격 - 유도 미사일 발사\n";
//    projectiles.emplace_back(std::make_unique<Missile>(playerPosition)); // 유도 미사일 생성
//}
//
//// 필살기 (현재는 구현 없음)
//void SkyPlayerAttack::ultimate_attack() {
//    std::cout << "Sky Stage: 필살기 - 아군 비행기 지원 공격\n";
//    // 필살기 구현 추가 가능
//}
//
//void SkyPlayerAttack::updateProjectiles() {
//
//    for (auto& projectile : projectiles) {
//        projectile->update(); // 발사체 상태 업데이트
//    }
//
//    projectiles.erase(
//        std::remove_if(projectiles.begin(), projectiles.end(),
//            [](const std::unique_ptr<Projectile>& projectile) {
//                return projectile->isOffScreen(); // 화면 크기를 사용
//            }),
//        projectiles.end());
//
//}
//
//void SkyPlayerAttack::drawProjectiles(sf::RenderWindow& window) {
//    for (auto& projectile : projectiles) {
//        projectile->draw(window); // 발사체 화면에 그리기
//    }
//}