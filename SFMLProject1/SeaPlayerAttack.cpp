#include "SeaPlayerAttack.h"
#include "Bullet.h"
#include "Torpedo.h"

SeaPlayerAttack::SeaPlayerAttack()
    : bulletDirection(1.0f, 0.0f) { // ó������ ������ �������� ����
}
// ���� ��ȯ�� ���� �Է� ó�� �޼���
void SeaPlayerAttack::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        bulletDirection = sf::Vector2f(-1.0f, 0.0f); // ���� ����
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        bulletDirection = sf::Vector2f(1.0f, 0.0f); // ������ ����
    }
}

// �⺻ ���� ����: �Ѿ��� �����Ͽ� ���������� �߻�
void SeaPlayerAttack::basic_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sea Stage: �⺻ ���� - �Ѿ� �߻�\n";
    projectiles.emplace_back(std::make_unique<Bullet>(playerPosition, bulletDirection)); // ���������� �߻�
}

// Ư�� ���� ����: ��� ����
void SeaPlayerAttack::special_attack(const sf::Vector2f& playerPosition) {
    std::cout << "Sea Stage: Ư�� ���� - ��� �߻�\n";
    projectiles.emplace_back(std::make_unique<Torpedo>(playerPosition)); // ��� �߻�
}

// �ʻ�� (����� ���� ����)
void SeaPlayerAttack::ultimate_attack() {
    std::cout << "Sea Stage: �ʻ�� - ��Ը� ���� ����\n";
    // �ʻ�� ���� �߰� ����
}

// �߻�ü ������Ʈ �� ȭ�鿡 �׸���
void SeaPlayerAttack::updateProjectiles(sf::RenderWindow& window) {
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
