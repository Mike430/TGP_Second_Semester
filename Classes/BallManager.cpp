#include "BallManager.h"


BallManager::BallManager()
{
}


BallManager::~BallManager()
{
}

void BallManager::CreateBall()
{
	Ball* newBall = new Ball();
	_balls.push_back(newBall);
}

void BallManager::DestroyBall(int index)
{
	delete _balls.at(index);
	_balls.at(index) = nullptr;
	
	_balls.erase(_balls.begin() + index);
}