#include "Tutorial_Scene.h"

// Initialisers
//==============================================================================
cocos2d::Scene* Tutorial_Scene::createScene()
{
	auto scene = Game_Scene::createScene();
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

	scene = Director::getInstance()->getRunningScene();

	game = scene->getChildByName<Game_Scene*>("Game_Scene");

	//this->scheduleUpdate();

	return true;
}
