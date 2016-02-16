#include "BallManager.h"


BallManager::BallManager()
{
}


BallManager::~BallManager()
{
}

Ball* BallManager::CreateBall(cocos2d::Node* parent)
{
	Ball* asdf = ZeroGravityBall::createZeroGravity(); // <-- ?
	Ball* newBall = (Ball*)asdf;
	parent->addChild(newBall);
	_balls.push_back(newBall);
	return newBall;
}

void BallManager::DestroyBall(int index)
{
	_balls[index]->getParent()->removeChild(_balls[index]);
	_balls.erase(_balls.begin() + index);
}


void BallManager::DestroyBall(Ball* ball)
{
	DestroyBall(find(begin(_balls), end(_balls), ball) - begin(_balls));
}