#pragma once
#include "Ball.h"

class BombOther : public Ball
{
public:
	static BombOther* create();
	virtual bool init() override;
	virtual ~BombOther();

};