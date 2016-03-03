#pragma once
#include "Ball.h"
class RocketBall : public Ball
{
public:
	static RocketBall* create();
	virtual bool init() override;
	virtual ~RocketBall();
	virtual void Hit(Vec2 velocity) override;
};

