#pragma once
#include "Ball.h"
#include "PoundSign.h"

class WalletBall : public Ball
{
public:
	static WalletBall* create();
	virtual bool init() override;
	virtual ~WalletBall();
	virtual void Hit(Vec2 velocity) override;
};
