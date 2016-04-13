#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
#include "Target.h"

using namespace std;
using namespace cocos2d;

class HalfGravFieldFX : public Target
{
public:
	static const int type = 4;
	virtual int getType() override { return type; }
	HalfGravFieldFX() {};
	virtual ~HalfGravFieldFX() {};
	CREATE_FUNC(HalfGravFieldFX);
	virtual bool init();
	virtual void Hit(Game_Scene* game, Ball* ball) override;
	virtual int GetScoreValue() const override;
};
