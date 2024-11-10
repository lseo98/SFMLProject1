#include "SeaAttackStrategy.h"
#include "Bullet.h"
#include "Torpedo.h"

// 기본 공격 구현: 총알을 생성하여 오른쪽으로 발사
void SeaAttackStrategy::basic_attack(const sf::Vector2f& playerPosition) {
   // std::cout << "Sea Stage: 기본 공격 - 총알 발사\n";
    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, sf::Vector2f(1.0f, 0.0f))); // 오른쪽으로 발사
}

// 특수 공격 구현: 어뢰 생성
void SeaAttackStrategy::special_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sea Stage: 특수 공격 - 어뢰 발사\n";
    projectiles.emplace_back(std::make_unique<Torpedo>(playerPosition)); // 어뢰 발사
}

// 필살기 (현재는 구현 없음)
void SeaAttackStrategy::ultimate_attack() {
    std::cout << "Sea Stage: 필살기 - 대규모 수중 폭발\n";
    // 필살기 구현 추가 가능
}

// 발사체 업데이트 및 화면에 그리기
void SeaAttackStrategy::updateProjectiles(sf::RenderWindow& window) {
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
