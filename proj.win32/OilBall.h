#pragma once
#include "Ball.h"
class OilBall : public Ball
{
public:
	static OilBall* create();
	virtual bool init() override;
	virtual ~OilBall();
	virtual void Hit(Vec2 velocity) override;
};
