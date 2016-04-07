#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class Tutorial_Scene : public Layer
{
public:
	CREATE_FUNC(Tutorial_Scene);
	static cocos2d::Scene* createScene();
	virtual bool init();
};

