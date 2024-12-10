//// Minigame.cpp
//
//#include "Minigame.h"
//
//// �����ڸ� ���� ��ü ���� �� ������� �̴ϰ����� �߻� Ƚ���� �޾� ��� ������ ����
//Minigame::Minigame(int minigameOccured) {
//	m_minigameOccured = minigameOccured;
//	m_minigameSuccessed = true;
//	m_keyArray[0] = 3 + minigameOccured;
//	m_keyArray[1] = 0;
//	m_keyArray[2] = 0;
//	clock = 0;
//}
//
//// Ÿ�� Ű ���͸� �ʱ�ȭ�ϴ� �Լ�
//void Minigame::initTargetKeys() {
//	for (int i = 0; i < 3 + m_minigameOccured; i++) {
//		targetKeys.clear();
//		targetKeys.push_back(rand() % 10);
//	}
//}
//
//// �Էµ� Ű�� Ÿ�� Ű�� ���Ͽ� �����ϸ� ������ ���� �޺κп��� Ÿ�� Ű ���� ���� ���� Ÿ�� Ű�� �Ѿ���� �ϴ� �Լ�
//void Minigame::checkTargetKeys(int key) {
//	if (targetKeys[targetKeys.size() - 1] == key) {
//		targetKeys.pop_back();
//	}
//	else {
//		initTargetKeys(); // �Էµ� Ű�� Ÿ�� Ű�� �ٸ��� �Է� ���з� �����Ͽ� Ÿ�� Ű �迭�� �ʱ� ���·� �ٽ� �����ϰ� ����
//	}
//	// m_keyArray �� �ε��� 0 �ڸ����� ���� �Է� Ű�� ������ ������Ʈ, �ε��� 2 �ڸ����� �Է��ؾ� �� Ű�� ���� ������Ʈ
//	m_keyArray[0] = targetKeys.size();
//	m_keyArray[2] = targetKeys[targetKeys.size() - 1];
//}
//
//// �̴ϰ����� �����ϴ� �Լ�
//void Minigame::runMinigame(float deltaTime) {
//	clock += deltaTime;
//	initTargetKeys();
//
//	// �̴ϰ��� ���� �� ���� �ð��� 5�ʰ� �Ѿ�� ���з� �����Ͽ� m_minigameSuccessed ������ false
//	if (clock >= 5) {
//		m_minigameSuccessed = false;
//	}
//	else {
//		// �Էµ� Ű���� ���� �ش� Ű�� �������� �´� üũ�� ����
//		// m_keyArray �� �ε��� 1 �ڸ��� ���� �Էµ� Ű ���� ����
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
//			m_keyArray[1] = 1;
//			checkTargetKeys(1);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::2)) {
//			m_keyArray[1] = 2;
//			checkTargetKeys(2);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::3)) {
//			m_keyArray[1] = 3;
//			checkTargetKeys(3);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::4)) {
//			m_keyArray[1] = 4;
//			checkTargetKeys(4);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::5)) {
//			m_keyArray[1] = 5;
//			checkTargetKeys(5);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::6)) {
//			m_keyArray[1] = 6;
//			checkTargetKeys(6);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::7)) {
//			m_keyArray[1] = 7;
//			checkTargetKeys(7);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::8)) {
//			m_keyArray[1] = 8;
//			checkTargetKeys(8);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::9)) {
//			m_keyArray[1] = 9;
//			checkTargetKeys(9);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::0)) {
//			m_keyArray[1] = 0;
//			checkTargetKeys(0);
//		}
//	}
//}