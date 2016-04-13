#pragma once
#include "Target.h"

using namespace std;
using namespace cocos2d;

class Double_Attack : public Target
{
public:
	static const int type = 6;
	virtual int getType() override { return type; }
	Double_Attack();
	virtual ~Double_Attack();

	CREATE_FUNC(Double_Attack);
	virtual bool init();
	virtual void Hit(Game_Scene* game, Ball* ball) override;
	virtual int GetScoreValue() const override;
};

