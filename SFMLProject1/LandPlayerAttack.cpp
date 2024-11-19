#include "LandPlayerAttack.h"
#include "Bullet.h"
#include "AntiTankMissile.h"

extern int WINDOWWIDTH, WINDOWHEIGHT;

LandPlayerAttack::LandPlayerAttack()
    : bulletDirection(1.0f, 0.0f) { // 처음에는 오른쪽 방향으로 설정
}

// 방향 전환을 위한 입력 처리 메서드
void LandPlayerAttack::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        bulletDirection = sf::Vector2f(-1.0f, 0.0f); // 왼쪽 방향
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        bulletDirection = sf::Vector2f(1.0f, 0.0f); // 오른쪽 방향
    }
}

// 기본 공격 구현: 총알을 생성하여 왼쪽 또는 오른쪽으로 발사
void LandPlayerAttack::basic_attack(const sf::Vector2f& playerPosition) {
    //std::cout << "Land Stage: 기본 공격 - 총알 발사\n";
    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, bulletDirection)); // 현재 방향으로 발사
}

// 특수 공격 구현: 대전차 미사일 생성
void LandPlayerAttack::special_attack(const sf::Vector2f & playerPosition) {
    std::cout << "Land Stage: 특수 공격 - 대전차 미사일 발사\n";
    projectiles.emplace_back(std::make_unique<AntiTankMissile>(playerPosition)); // 대전차 미사일 생성
}

// 필살기 (현재는 구현 없음)
void LandPlayerAttack::ultimate_attack() {
    std::cout << "Land Stage: 필살기 - 대규모 지상 폭발\n";
    // 필살기 구현 추가 가능
}

// 발사체 업데이트
void LandPlayerAttack::updateProjectiles() {
    handleInput(); // 방향 입력 확인

    for (auto& projectile : projectiles) {
        projectile->update(); // 발사체 상태 업데이트
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [](const std::unique_ptr<Projectile>& projectile) {
                return projectile->isOffScreen(); // 화면 크기를 사용
            }),
        projectiles.end());
}

// 발사체 화면에 그리기
void LandPlayerAttack::drawProjectiles(sf::RenderWindow& window) {
    for (auto& projectile : projectiles) {
        projectile->draw(window); // 발사체 화면에 그리기
    }
}
