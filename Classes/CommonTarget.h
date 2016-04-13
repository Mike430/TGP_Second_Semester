#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
#include "Target.h"

using namespace std;
using namespace cocos2d;

class CommonTarget : public Target
{
public:
	static const int type = 7;
	virtual int getType() override { return type; }
	CommonTarget() {};
	virtual ~CommonTarget() {};
	CREATE_FUNC(CommonTarget);
	virtual bool init();
	virtual void Hit(Game_Scene* game, Ball* ball) override;
	virtual int GetScoreValue() const override;
};
