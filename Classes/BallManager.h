#pragma once
#ifndef __BALL_MANAGER_H__
#define __BALL_MANAGER_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Ball.h"
#include <vector>

using namespace std;

class BallManager
{
private:
	vector<Ball*> _balls;
public:
	BallManager();
	~BallManager();

	void CreateBall();
	void DestroyBall(int index);
	int GetNumberOfBalls() const { return _balls.size(); };
};
#endif // __BALL_MANAGER_H__
