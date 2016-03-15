#pragma once
#include "Ball.h"
class PowderBall : public Ball
{
public:
	static PowderBall* create();
	virtual bool init() override;
	virtual ~PowderBall();
	//virtual void Hit(Vec2 velocity) override;
};