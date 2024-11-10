#include "SkyAttackStrategy.h"
#include "Bullet.h"
#include "Missile.h"

// 기본 공격 구현: 총알을 생성하여 위쪽으로 발사
void SkyAttackStrategy::basic_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sky Stage: 기본 공격 - 총알 발사\n";
    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, sf::Vector2f(0.0f, -1.0f))); // 위쪽으로 발사
}

// 특수 공격 구현: 유도 미사일 생성
void SkyAttackStrategy::special_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sky Stage: 특수 공격 - 유도 미사일 발사\n";
    projectiles.emplace_back(std::make_unique<Missile>(playerPosition)); // 유도 미사일 생성
}

// 필살기 (현재는 구현 없음)
void SkyAttackStrategy::ultimate_attack() {
    std::cout << "Sky Stage: 필살기 - 아군 비행기 지원 공격\n";
    // 필살기 구현 추가 가능
}

// 발사체 업데이트 및 화면에 그리기
void SkyAttackStrategy::updateProjectiles(sf::RenderWindow& window) {
    for (auto& projectile : projectiles) {
        projectile->update();
        projectile->draw(window);
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                       [&window](const std::unique_ptr<Projectile>& projectile) {
                           return projectile->isOffScreen(window.getSize().x, window.getSize().y);
                       }),
        projectiles.end());
}
