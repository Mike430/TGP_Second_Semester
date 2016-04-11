#pragma once
#ifndef __BALL_MANAGER_H__
#define __BALL_MANAGER_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Ball.h"
#include "ZeroGravityBall.h"
#include "RocketBall.h"
#include <vector>
#include <unordered_map>
#include <set>
#include "BombBall.h"
#include "PowderBall.h"
#include "OilBall.h"
#include "WalletBall.h"
#include "BombOther.h"
#include "SubPowder.h"

using namespace std;

class BallManager
{
private:
	vector<Ball*> _balls;
	unordered_map<int, float> _ballChance;//ball type -> chance of spawning
	float _totalChance;//sum of chances of enabled balls, divide by this to get actual chance
	set<int> _enabledBalls;
public:
	BallManager();
	~BallManager();

	Ball* CreateBall(cocos2d::Node* parent, bool bypass);
	void AddBall(Node* parent, Ball* ball);
	void DestroyBall(int index);
	void DestroyBall(Ball* ball);
	int GetNumberOfBalls() const { return _balls.size(); };
	Ball* GetBallAtIndex(int index) const { return _balls.at(index); }
	void EnableBall(int ballType);
};
#endif // __BALL_MANAGER_H__
