#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
#include "Target.h"

using namespace std;
using namespace cocos2d;

class RareTarget : public Target
{
public:
	RareTarget() {};
	virtual ~RareTarget() {};
	CREATE_FUNC(RareTarget);
	virtual bool init();
	virtual void Hit(Game_Scene* game, Ball* ball) override;
	virtual int GetScoreValue() const override;
};
