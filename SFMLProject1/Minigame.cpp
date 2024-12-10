//// Minigame.cpp
//
//#include "Minigame.h"
//
//// 생성자를 통해 객체 생성 시 현재까지 미니게임의 발생 횟수를 받아 멤버 변수에 저장
//Minigame::Minigame(int minigameOccured) {
//	m_minigameOccured = minigameOccured;
//	m_minigameSuccessed = true;
//	m_keyArray[0] = 3 + minigameOccured;
//	m_keyArray[1] = 0;
//	m_keyArray[2] = 0;
//	clock = 0;
//}
//
//// 타깃 키 벡터를 초기화하는 함수
//void Minigame::initTargetKeys() {
//	for (int i = 0; i < 3 + m_minigameOccured; i++) {
//		targetKeys.clear();
//		targetKeys.push_back(rand() % 10);
//	}
//}
//
//// 입력된 키와 타깃 키를 비교하여 성공하면 벡터의 가장 뒷부분에서 타깃 키 값을 빼내 다음 타깃 키로 넘어가도록 하는 함수
//void Minigame::checkTargetKeys(int key) {
//	if (targetKeys[targetKeys.size() - 1] == key) {
//		targetKeys.pop_back();
//	}
//	else {
//		initTargetKeys(); // 입력된 키와 타깃 키가 다르면 입력 실패로 간주하여 타깃 키 배열을 초기 상태로 다시 랜덤하게 생성
//	}
//	// m_keyArray 의 인덱스 0 자리에는 남은 입력 키의 개수를 업데이트, 인덱스 2 자리에는 입력해야 할 키의 값을 업데이트
//	m_keyArray[0] = targetKeys.size();
//	m_keyArray[2] = targetKeys[targetKeys.size() - 1];
//}
//
//// 미니게임을 실행하는 함수
//void Minigame::runMinigame(float deltaTime) {
//	clock += deltaTime;
//	initTargetKeys();
//
//	// 미니게임 시작 후 제한 시간인 5초가 넘어가면 실패로 간주하여 m_minigameSuccessed 변수에 false
//	if (clock >= 5) {
//		m_minigameSuccessed = false;
//	}
//	else {
//		// 입력된 키값에 따라 해당 키의 정수값에 맞는 체크를 실행
//		// m_keyArray 의 인덱스 1 자리에 현재 입력된 키 값을 저장
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