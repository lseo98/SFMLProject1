// Minigame.cpp

#include "Minigame.h"

// �����ڸ� ���� ��ü ���� �� ������� �̴ϰ����� �߻� Ƚ���� �޾� ��� ������ ����
Minigame::Minigame(int minigameOccured) {
	this->minigameOccured = minigameOccured;
	minigameSuccessed = false; 
	badEnding = false;
	m_keyArray[0] = defaultOccure + minigameOccured;
	m_keyArray[1] = 0;
	m_keyArray[2] = 0;
	clock = 0;

	initTargetKeys();
}

// Ÿ�� Ű ���͸� �ʱ�ȭ�ϴ� �Լ�
void Minigame::initTargetKeys() {
	correctCnt = 0;
	for (int i = 0; i < defaultOccure + minigameOccured; i++) {
		targetKeys[i] = rand() % 10;
	}
	m_keyArray[2] = targetKeys[correctCnt];
}

// �Էµ� Ű�� Ÿ�� Ű�� ���Ͽ� �����ϸ� ������ ���� �޺κп��� Ÿ�� Ű ���� ���� ���� Ÿ�� Ű�� �Ѿ���� �ϴ� �Լ�
bool Minigame::checkTargetKeys(int key) {
	//std::cout << key << std::endl;

	if (targetKeys[correctCnt] == key) {
		correctCnt++;
	}
	else {
		initTargetKeys(); // �Էµ� Ű�� Ÿ�� Ű�� �ٸ��� �Է� ���з� �����Ͽ� Ÿ�� Ű �迭�� �ʱ� ���·� �ٽ� �����ϰ� ����
		return false;
	}
	// m_keyArray �� �ε��� 0 �ڸ����� ���� �Է� Ű�� ������ ������Ʈ, �ε��� 2 �ڸ����� �Է��ؾ� �� Ű�� ���� ������Ʈ
	m_keyArray[0] = defaultOccure + minigameOccured - correctCnt;
	m_keyArray[2] = targetKeys[correctCnt];
	return true;
}

// �̴ϰ����� �����ϴ� �Լ�
void Minigame::runMinigame(float deltaTime, int *minigameArr, sf::RenderWindow& window) {
	clock += deltaTime;

	window.pollEvent(event);
	//std::cout << m_keyArray[1] << std::endl;
	// �̴ϰ��� ���� �� ���� �ð��� 5�ʰ� �Ѿ�� ���з� �����Ͽ� m_minigameSuccessed ������ false
	if (clock >= 5) {
		minigameSuccessed = false;
		badEnding = true;
	}
	else if (event.type == sf::Event::KeyPressed) {
		// �Էµ� Ű���� ���� �ش� Ű�� �������� �´� üũ�� ����
		// m_keyArray �� �ε��� 1 �ڸ��� ���� �Էµ� Ű ���� ����
		switch (event.key.code) {
		case sf::Keyboard::Num0:		// ���� �� ����Ű
		case sf::Keyboard::Numpad0:		// ���� �е� ����Ű
			m_keyArray[1] = 0;
			break;
		case sf::Keyboard::Num1:
		case sf::Keyboard::Numpad1:
			m_keyArray[1] = 1;
			break;
		case sf::Keyboard::Num2:
		case sf::Keyboard::Numpad2:
			m_keyArray[1] = 2;
			break;
		case sf::Keyboard::Num3:
		case sf::Keyboard::Numpad3:
			m_keyArray[1] = 3;
			break;
		case sf::Keyboard::Num4:
		case sf::Keyboard::Numpad4:
			m_keyArray[1] = 4;
			break;
		case sf::Keyboard::Num5:
		case sf::Keyboard::Numpad5:
			m_keyArray[1] = 5;
			break;
		case sf::Keyboard::Num6:
		case sf::Keyboard::Numpad6:
			m_keyArray[1] = 6;
			break;
		case sf::Keyboard::Num7:
		case sf::Keyboard::Numpad7:
			m_keyArray[1] = 7;
			break;
		case sf::Keyboard::Num8:
		case sf::Keyboard::Numpad8:
			m_keyArray[1] = 8;
			break;
		case sf::Keyboard::Num9:
		case sf::Keyboard::Numpad9:
			m_keyArray[1] = 9;
			break;
		default:
			m_keyArray[1] = -1; // �߸��� Ű �Է�
			break;
			//std::cout << m_keyArray[1] << std::endl;
			
		}
		checkTargetKeys(m_keyArray[1]);
		
	}
	for (int i = 0; i < 3; i++) minigameArr[i] = m_keyArray[i];
	
	if (defaultOccure + minigameOccured == correctCnt) {
		minigameSuccessed = true;
	}
}
