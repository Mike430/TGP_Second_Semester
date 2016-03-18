#pragma once
#include "Ball.h"
class SubPowder : public Ball
{
public:
	static const int type = 20;
	//bool _contained = false;
	static SubPowder* create();
	virtual bool init() override;
	virtual ~SubPowder();
	virtual void Hit(Vec2 velocity) override;
	virtual void update(float deltaTime) override;
	virtual int getType() override { return type; }
};
