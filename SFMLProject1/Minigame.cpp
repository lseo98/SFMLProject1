// Minigame.cpp

#include "Minigame.h"

// 생성자를 통해 객체 생성 시 현재까지 미니게임의 발생 횟수를 받아 멤버 변수에 저장
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

// 타깃 키 벡터를 초기화하는 함수
void Minigame::initTargetKeys() {
	correctCnt = 0;
	for (int i = 0; i < defaultOccure + minigameOccured; i++) {
		targetKeys[i] = rand() % 10;
	}
	m_keyArray[2] = targetKeys[correctCnt];
}

// 입력된 키와 타깃 키를 비교하여 성공하면 벡터의 가장 뒷부분에서 타깃 키 값을 빼내 다음 타깃 키로 넘어가도록 하는 함수
bool Minigame::checkTargetKeys(int key) {
	//std::cout << key << std::endl;

	if (targetKeys[correctCnt] == key) {
		correctCnt++;
	}
	else {
		initTargetKeys(); // 입력된 키와 타깃 키가 다르면 입력 실패로 간주하여 타깃 키 배열을 초기 상태로 다시 랜덤하게 생성
		return false;
	}
	// m_keyArray 의 인덱스 0 자리에는 남은 입력 키의 개수를 업데이트, 인덱스 2 자리에는 입력해야 할 키의 값을 업데이트
	m_keyArray[0] = defaultOccure + minigameOccured - correctCnt;
	m_keyArray[2] = targetKeys[correctCnt];
	return true;
}

// 미니게임을 실행하는 함수
void Minigame::runMinigame(float deltaTime, int *minigameArr, sf::RenderWindow& window) {
	clock += deltaTime;

	window.pollEvent(event);
	//std::cout << m_keyArray[1] << std::endl;
	// 미니게임 시작 후 제한 시간인 5초가 넘어가면 실패로 간주하여 m_minigameSuccessed 변수에 false
	if (clock >= 5) {
		minigameSuccessed = false;
		badEnding = true;
	}
	else if (event.type == sf::Event::KeyPressed) {
		// 입력된 키값에 따라 해당 키의 정수값에 맞는 체크를 실행
		// m_keyArray 의 인덱스 1 자리에 현재 입력된 키 값을 저장
		switch (event.key.code) {
		case sf::Keyboard::Num0:		// 자판 위 숫자키
		case sf::Keyboard::Numpad0:		// 숫자 패드 숫자키
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
			m_keyArray[1] = -1; // 잘못된 키 입력
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
