#include "BallManager.h"

BallManager::BallManager()
{
	_ballChance = unordered_map<int, float>{
		{ Ball::type, 60.0f },
		{ WalletBall::type, 5.0f },
		{ BombBall::type, 5.0f },
		{ PowderBall::type, 1.0f },
		{ OilBall::type, 9.0f },
		{ RocketBall::type, 10.0f },
		{ BombOther::type, 10.0f }
	};
	_ballEnableTimes = unordered_map<int, int>{
		{ 10, RocketBall::type },
		{ 20, OilBall::type },
		{ 30, BombOther::type },
		{ 36, BombBall::type },
		{ 44, WalletBall::type },
		{ 50, PowderBall::type }
	};
	//enable basic ball to start with
	EnableBall(Ball::type);
}

BallManager::~BallManager()
{
}

Ball* BallManager::CreateBall(cocos2d::Node* parent, bool bypass)
{
	//or would you prefer templates?
	static const auto createBallFromType = [](int type)
	{
		Ball* newBall = nullptr;
		switch (type)
		{
		case Ball::type:		newBall = Ball::create(); break;
		case WalletBall::type:	newBall = WalletBall::create(); break;
		case BombBall::type:	newBall = BombBall::create(); break;
		case PowderBall::type:	newBall = PowderBall::create(); break;
		case OilBall::type:		newBall = OilBall::create(); break;
		case RocketBall::type:	newBall = RocketBall::create(); break;
		case BombOther::type:	newBall = BombOther::create(); break;
		}
		return newBall;
	};
	//random enabled ball based on chances
	//	example:
	//	Ball: 60, WalletBall: 5   -> _totalChance = 65
	//	random number up to total = 63
	//	not smaller than 60, take away the 60, leaving 3
	//	3 smaller than WalletBalls 5, to create a WalletBall
	int ballType = 0;
	float rnd = RandomHelper::random_real(0.0f, _totalChance);
	for (const auto enabledType : _enabledBalls)
	{
		float chance = _ballChance[enabledType];
		if (rnd <= chance)
		{
			ballType = enabledType;
			break;
		}
		rnd -= chance;
	}
	//create new ball
	Ball* newBall = createBallFromType(ballType);
	AddBall(parent, newBall);
	//Possibly enable new ball type
	_spawnedBalls++;
	auto it = _ballEnableTimes.find(_spawnedBalls);
	if (it != _ballEnableTimes.end())
	{
		EnableBall(it->second);
	}
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

void BallManager::AddBall(Node* parent, Ball* ball)
{
	parent->addChild(ball);
	_balls.push_back(ball);
}

void BallManager::EnableBall(int ballType)
{
	_enabledBalls.insert(ballType);
	_totalChance += _ballChance[ballType];
}
