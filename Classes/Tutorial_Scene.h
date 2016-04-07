#pragma once

#include "cocos2d.h"
#include "Game_Scene.h"
using namespace cocos2d;

class Tutorial_Scene : public Layer
{
private:
	Scene* scene;
	Game_Scene* game;
public:
	CREATE_FUNC(Tutorial_Scene);
	static cocos2d::Scene* createScene();
	virtual bool init();
};

