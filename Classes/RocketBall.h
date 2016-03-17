#pragma once
#include "Ball.h"
class RocketBall : public Ball
{
public:
	static const int type = 1;
	static RocketBall* create();
	virtual bool init() override;
	virtual ~RocketBall();
	virtual void Hit(Vec2 velocity) override;
	virtual int getType() override { return type; }
};

