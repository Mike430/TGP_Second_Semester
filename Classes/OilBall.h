#pragma once
#include "Ball.h"
class OilBall : public Ball
{
public:
	static const int type = 10;
	static OilBall* create();
	virtual bool init() override;
	virtual ~OilBall();
};
