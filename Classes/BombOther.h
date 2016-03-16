#pragma once
#include "Ball.h"

class BombOther : public Ball
{
public:
	static const int type = 8;
	static BombOther* create();
	virtual bool init() override;
	virtual ~BombOther();
};