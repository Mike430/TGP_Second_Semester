#pragma once
#include "Ball.h"
class ZeroGravityBall : public Ball
{
public:
	static const int type = -1;
	static ZeroGravityBall* createZeroGravity();
	virtual bool init() override;
	virtual ~ZeroGravityBall();
	virtual void Setup(Vec2 startPoint, Vec2 next, bool onRight) override;
	virtual void Hit(Vec2 velocity) override;
};

