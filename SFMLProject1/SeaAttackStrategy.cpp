#include "SeaAttackStrategy.h"
#include "Bullet.h"
#include "Torpedo.h"

// �⺻ ���� ����: �Ѿ��� �����Ͽ� ���������� �߻�
void SeaAttackStrategy::basic_attack(const sf::Vector2f& playerPosition) {
   // std::cout << "Sea Stage: �⺻ ���� - �Ѿ� �߻�\n";
    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, sf::Vector2f(1.0f, 0.0f))); // ���������� �߻�
}

// Ư�� ���� ����: ��� ����
void SeaAttackStrategy::special_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sea Stage: Ư�� ���� - ��� �߻�\n";
    projectiles.emplace_back(std::make_unique<Torpedo>(playerPosition)); // ��� �߻�
}

// �ʻ�� (����� ���� ����)
void SeaAttackStrategy::ultimate_attack() {
    std::cout << "Sea Stage: �ʻ�� - ��Ը� ���� ����\n";
    // �ʻ�� ���� �߰� ����
}

// �߻�ü ������Ʈ �� ȭ�鿡 �׸���
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
