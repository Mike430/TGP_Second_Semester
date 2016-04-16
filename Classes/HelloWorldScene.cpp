#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Tutorial_Scene.h"
#include "Game_Scene.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _rootNode = CSLoader::createNode("0_Main_Menu.csb");
    addChild(_rootNode);

	_gameScene = nullptr;

	_beginButton = (cocos2d::ui::Button*)_rootNode->getChildByName("Begin_Button");
	_beginButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::BeginButtonPressed, this));
	_tutorialButton = _rootNode->getChildByName<cocos2d::ui::Button*>("Tutorial_Button");
	_tutorialButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::TutorialButtonPressed, this));
	AnimationHelper::PreLoadAnimation("Intro", 170, 1280, 800, 24, "Frame - ", ".jpg");

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("res/Audio/Menusong.mp3", true);

    return true;
}

void HelloWorld::BeginButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{

	if (_gameScene == nullptr)
	{
		Sprite* test = _rootNode->getChildByName<Sprite*>("Background");
		
		Vec2 ButtonTarget = Vec2 (640, -70);
		auto MoveButtonsOut = MoveTo::create(2, ButtonTarget);
		auto MoveButtonsOut2 = MoveTo::create(2, ButtonTarget);
		_beginButton->runAction(MoveButtonsOut2);
		_tutorialButton->runAction(MoveButtonsOut);
		//_beginButton->setOpacity(0);
		//_tutorialButton->setOpacity(0);
		AnimationHelper::Animate(test, "Intro");
		runAction(Sequence::create(DelayTime::create(7.08f), CallFunc::create(CC_CALLBACK_0(HelloWorld::LoadGame, this)), nullptr));

		

       // CCDirector::getInstance()->replaceScene(TransitionFadeBL::create(2.0f, _gameScene));
        
	}
}


void HelloWorld::TutorialButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (_gameScene == nullptr)
	{
		_gameScene = Tutorial_Scene::createScene();
		CCDirector::getInstance()->replaceScene(_gameScene);
	}
}

void HelloWorld::LoadGame()
{
	_gameScene = Game_Scene::createScene();
	CCDirector::getInstance()->replaceScene(_gameScene);
}