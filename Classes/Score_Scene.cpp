#include "Score_Scene.h"

using namespace cocostudio::timeline;

cocos2d::Scene* Score_Scene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();

	// 'layer' is an autorelease object
	auto layer = Score_Scene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Score_Scene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_rootNode = cocos2d::CSLoader::createNode("2_Score_Scene.csb");
	addChild(_rootNode);

	_playAgainButton = (cocos2d::ui::Button*)_rootNode->getChildByName("Play_Again");
	_playAgainButton->addTouchEventListener(CC_CALLBACK_2(Score_Scene::PlayAgainButtonPressed, this));

	_mainMenuButton = (cocos2d::ui::Button*)_rootNode->getChildByName("Main_Menu");
	_mainMenuButton->addTouchEventListener(CC_CALLBACK_2(Score_Scene::MainMenuButtonPressed, this));

	return true;
}

void Score_Scene::PlayAgainButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	cocos2d::Scene* newGame = Game_Scene::createScene();
	cocos2d::CCDirector::getInstance()->replaceScene(newGame);
}

void Score_Scene::MainMenuButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	cocos2d::Scene* mainMenu = HelloWorld::createScene();
	cocos2d::CCDirector::getInstance()->replaceScene(mainMenu);
}