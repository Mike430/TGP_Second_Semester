#pragma once
#include "Target.h"

using namespace std;
using namespace cocos2d;

class Invincibility : public Target
{
public:
	Invincibility();
	virtual ~Invincibility();

	CREATE_FUNC(Invincibility);
	virtual bool init();
	virtual void Hit(Game_Scene* game, Ball* ball) override;
	virtual int GetScoreValue() const override;
};
