#pragma once
#include "Ball.h"
class SubPowder : public Ball
{
public:
	static SubPowder* create();
	virtual bool init() override;
	virtual ~SubPowder();
	virtual void Hit(Vec2 velocity) override;
};
