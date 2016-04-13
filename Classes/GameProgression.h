#pragma once

#include <vector>
#include <functional>
#include "BallManager.h"
#include "TargetManager.h"
using namespace std;

class GameProgression
{
private:
	vector<pair<float, function<void()>>> _events;
	float _currentTime = 0;
	Game_Scene* _game;
public:
	GameProgression(Game_Scene* game);
	~GameProgression();
	void Update(float deltaTime);
	void EnableBall(int ballType);
	void EnableTarget(int targetType);
	int GetRemainingEvents();
};

