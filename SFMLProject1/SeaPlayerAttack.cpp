#include "SeaPlayerAttack.h"
#include "Bullet.h"
#include "Torpedo.h"

extern int WINDOWWIDTH, WINDOWHEIGHT;

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
    //std::cout << "Sea Stage: �⺻ ���� - �Ѿ� �߻�\n";
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

void SeaPlayerAttack::updateProjectiles() {
    handleInput(); // ���� �Է� Ȯ��

    for (auto& projectile : projectiles) {
        projectile->update(); // �߻�ü ���� ������Ʈ
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [](const std::unique_ptr<Projectile>& projectile) {
                return projectile->isOffScreen(); // ȭ�� ũ�⸦ ���
            }),
        projectiles.end());
}

void SeaPlayerAttack::drawProjectiles(sf::RenderWindow& window) {
    for (auto& projectile : projectiles) {
        projectile->draw(window); // �߻�ü ȭ�鿡 �׸���
    }
}

