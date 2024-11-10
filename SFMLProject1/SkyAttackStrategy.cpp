#include "SkyAttackStrategy.h"
#include "Bullet.h"
#include "Missile.h"

// �⺻ ���� ����: �Ѿ��� �����Ͽ� �������� �߻�
void SkyAttackStrategy::basic_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sky Stage: �⺻ ���� - �Ѿ� �߻�\n";
    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, sf::Vector2f(0.0f, -1.0f))); // �������� �߻�
}

// Ư�� ���� ����: ���� �̻��� ����
void SkyAttackStrategy::special_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sky Stage: Ư�� ���� - ���� �̻��� �߻�\n";
    projectiles.emplace_back(std::make_unique<Missile>(playerPosition)); // ���� �̻��� ����
}

// �ʻ�� (����� ���� ����)
void SkyAttackStrategy::ultimate_attack() {
    std::cout << "Sky Stage: �ʻ�� - �Ʊ� ����� ���� ����\n";
    // �ʻ�� ���� �߰� ����
}

// �߻�ü ������Ʈ �� ȭ�鿡 �׸���
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
