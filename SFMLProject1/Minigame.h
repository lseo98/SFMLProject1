#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Minigame {
private:
	// ��� ���� �� ���� ����
	std::vector<int> targetKeys;
	int m_minigameOccured;
	bool m_minigameSuccessed;
	int m_keyArray[3];
	float clock;
public:
	// ������ ���� ���� �� �Լ� ����
	Minigame(int minigameOccured);
	~Minigame();
	void initTargetKeys();
	void checkTargetKeys(int key);
	void runMinigame(float deltaTime);
};