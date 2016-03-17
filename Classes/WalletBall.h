#pragma once
#include "Ball.h"
#include "PoundSign.h"

class WalletBall : public Ball
{
public:
	static const int type = 7;
	static WalletBall* create();
	virtual bool init() override;
	virtual ~WalletBall();
	virtual void Hit(Vec2 velocity) override;
	virtual int getType() override { return type; }
};
