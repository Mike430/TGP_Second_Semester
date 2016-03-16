#pragma once
#include "ball.h"
#include "Explosion.h"
//#include "Player.h"


class BombBall : public Ball
{
public:
	static const int type = 9;
	static BombBall* create();
	virtual bool init() override;
	virtual ~BombBall();
	//virtual void Setup(Vec2 startPoint, Vec2 next, bool onRight) override;
	virtual void Hit(Vec2 velocity) override;
};

