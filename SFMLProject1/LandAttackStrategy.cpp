#include "LandAttackStrategy.h"
#include "Bullet.h"
#include "AntiTankMissile.h"

LandAttackStrategy::LandAttackStrategy()
    : bulletDirection(1.0f, 0.0f) { // ó������ ������ �������� ����
}

// ���� ��ȯ�� ���� �Է� ó�� �޼���
void LandAttackStrategy::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        bulletDirection = sf::Vector2f(-1.0f, 0.0f); // ���� ����
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        bulletDirection = sf::Vector2f(1.0f, 0.0f); // ������ ����
    }
}

// �⺻ ���� ����: �Ѿ��� �����Ͽ� ���� �Ǵ� ���������� �߻�
void LandAttackStrategy::basic_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Land Stage: �⺻ ���� - �Ѿ� �߻�\n";
    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, bulletDirection)); // ���� �������� �߻�
}

// Ư�� ���� ����: ������ �̻��� ����
void LandAttackStrategy::special_attack(const sf::Vector2f & playerPosition) {
    std::cout << "Land Stage: Ư�� ���� - ������ �̻��� �߻�\n";
    projectiles.emplace_back(std::make_unique<AntiTankMissile>(playerPosition)); // ������ �̻��� ����
}

// �ʻ�� (����� ���� ����)
void LandAttackStrategy::ultimate_attack() {
    std::cout << "Land Stage: �ʻ�� - ��Ը� ���� ����\n";
    // �ʻ�� ���� �߰� ����
}

// �߻�ü ������Ʈ �� ȭ�鿡 �׸���
void LandAttackStrategy::updateProjectiles(sf::RenderWindow& window) {
    handleInput(); // �� �����Ӹ��� ���� �Է��� Ȯ���Ͽ� ���� ��ȯ

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