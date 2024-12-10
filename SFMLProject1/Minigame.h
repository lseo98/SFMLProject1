#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Minigame {

public:
	// ������ ���� ���� �� �Լ� ����
	Minigame(int minigameOccured);
	~Minigame();
	void initTargetKeys();
	bool checkTargetKeys(int key);
	void runMinigame(float deltaTime, int* minigameArr, sf::RenderWindow& window);
	bool getSuccess() { return minigameSuccessed; }
	bool getBadEnding() { return badEnding; }
	int countdownValue = 5; // ī��Ʈ�ٿ� �ʱ�ȭ
	sf::Clock countdownClock;    // ī��Ʈ�ٿ� Ÿ�̸�

	int getCountdownValue() const; // ���� ī��Ʈ�ٿ� ���� ��ȯ

private:
	// ��� ���� �� ���� ����
	//sf::RenderWindow* window;
 	sf::Event event;
	static const int defaultOccure = 3;
	int targetKeys[100 + defaultOccure];	// �ִ� �̴ϰ��� ȸ���� 100 + defaultOccureȸ
	int correctCnt;
	int minigameOccured;
	bool minigameSuccessed;
	bool badEnding;
	int m_keyArray[3];
	float clock;
};