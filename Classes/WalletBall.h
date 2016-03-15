#pragma once
#include "Ball.h"
class WalletBall : public Ball
{
public:
	static WalletBall* create();
	virtual bool init() override;
	virtual ~WalletBall();
	virtual void Hit(Vec2 velocity) override;
};
