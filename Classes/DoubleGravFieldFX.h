#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
#include "Target.h"

using namespace std;
using namespace cocos2d;

class DoubleGravFieldFX : public Target
{
public:
	DoubleGravFieldFX() {};
	virtual ~DoubleGravFieldFX() {};
	CREATE_FUNC(DoubleGravFieldFX);
	virtual bool init();
	virtual void Hit(Game_Scene* game) override;
	virtual int GetScoreValue() const override;
};
