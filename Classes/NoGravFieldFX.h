#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
#include "Target.h"

using namespace std;
using namespace cocos2d;

class NoGravFieldFX : public Target
{
public:
	NoGravFieldFX() {};
	virtual ~NoGravFieldFX() {};
	CREATE_FUNC(NoGravFieldFX);
	virtual bool init();
	virtual void Hit(Game_Scene* game) override;
	virtual int GetScoreValue() const override;
};
