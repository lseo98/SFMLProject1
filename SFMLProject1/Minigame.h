#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Minigame {
private:
	// 멤버 변수 및 벡터 선언
	std::vector<int> targetKeys;
	int m_minigameOccured;
	bool m_minigameSuccessed;
	int m_keyArray[3];
	float clock;
public:
	// 생성자 형태 지정 및 함수 정의
	Minigame(int minigameOccured);
	~Minigame();
	void initTargetKeys();
	void checkTargetKeys(int key);
	void runMinigame(float deltaTime);
};