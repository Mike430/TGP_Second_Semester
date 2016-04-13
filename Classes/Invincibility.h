#pragma once
#include "Target.h"

using namespace std;
using namespace cocos2d;

class Invincibility : public Target
{
public:
	static const int type = 3;
	virtual int getType() override { return type; }
	Invincibility();
	virtual ~Invincibility();

	// We define the create function for Invincibility
	CREATE_FUNC(Invincibility);

	virtual bool init();

	virtual void Hit(Game_Scene* game, Ball* ball) override;

	// Const means that it won't modify any values in the method
	virtual int GetScoreValue() const override;
};
