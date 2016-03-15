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
#include "BombBall.h"
#include "PowderBall.h"
#include "OilBall.h"
#include "WalletBall.h"

using namespace std;

class BallManager
{
private:
	vector<Ball*> _balls;
public:
	BallManager();
	~BallManager();

	Ball* CreateBall(cocos2d::Node* parent);
	void DestroyBall(int index);
	void DestroyBall(Ball* ball);
	int GetNumberOfBalls() const { return _balls.size(); };
	Ball* GetBallAtIndex(int index) const { return _balls.at(index); }
};
#endif // __BALL_MANAGER_H__
