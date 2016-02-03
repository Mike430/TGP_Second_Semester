#include "BallManager.h"


BallManager::BallManager()
{
}


BallManager::~BallManager()
{
}

void BallManager::AddBall(Ball* ball)
{
	_balls.push_back(ball);
}

void BallManager::CreateBall()
{
	Ball* newBall = Ball::create();
	_balls.push_back(newBall);
}

void BallManager::DestroyBall(int index)
{
	_balls[index]->getParent()->removeChild(_balls[index]);
	_balls.erase(_balls.begin() + index);
}