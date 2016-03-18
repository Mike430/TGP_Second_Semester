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
	void Setup(Vec2 position, bool onRight);
	virtual int getType() override { return type; }
};
