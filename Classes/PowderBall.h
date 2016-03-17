#pragma once
#include "Ball.h"
class PowderBall : public Ball
{
private:
	int subBalls;
public:
	static const int type = 13;
	static PowderBall* create();
	virtual bool init() override;
	virtual ~PowderBall();
	void releasePowder();
	//virtual void Hit(Vec2 velocity) override;
	virtual int getType() override { return type; }
};