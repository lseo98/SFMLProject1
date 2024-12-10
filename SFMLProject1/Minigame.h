#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Minigame {

public:
	// 생성자 형태 지정 및 함수 정의
	Minigame(int minigameOccured);
	~Minigame();
	void initTargetKeys();
	bool checkTargetKeys(int key);
	void runMinigame(float deltaTime, int* minigameArr, sf::RenderWindow& window);
	bool getSuccess() { return minigameSuccessed; }
	bool getBadEnding() { return badEnding; }

private:
	// 멤버 변수 및 벡터 선언
	//sf::RenderWindow* window;
 	sf::Event event;
	static const int defaultOccure = 1;
	int targetKeys[100 + defaultOccure];	// 최대 미니게임 회수는 100 + defaultOccure회
	int correctCnt;
	int minigameOccured;
	bool minigameSuccessed;
	bool badEnding;
	int m_keyArray[3];
	float clock;
};