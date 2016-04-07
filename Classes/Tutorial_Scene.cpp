#include "Tutorial_Scene.h"
#include "Game_Scene.h"

// Initialisers
//==============================================================================
cocos2d::Scene* Tutorial_Scene::createScene()
{
	auto scene = Game_Scene::createScene();
	//Game_Scene* game = (Game_Scene*)scene->layers[0];
	auto tutorial = Tutorial_Scene::create();
	scene->addChild(tutorial);
	return scene;
}

bool Tutorial_Scene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//this->scheduleUpdate();

	return true;
}
