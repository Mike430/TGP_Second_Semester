#include "Score_Scene.h"

using namespace cocostudio::timeline;

cocos2d::Scene* Score_Scene::createScene(int leftScore, int rightScore)
{
	// 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();

	// 'layer' is an autorelease object
	auto layer = Score_Scene::create();
	layer->setScores(leftScore, rightScore);

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

	this->scheduleUpdate();

	return true;
}

void Score_Scene::setScores(int leftScore, int rightScore)
{
	_leftScore = leftScore;
	_rightScore = rightScore;
	bool leftWon = _leftScore > _rightScore;
	string playerOneWinState;
	string playerTwoWinState;

	if (leftWon){
		playerOneWinState = "WINNER";
		playerTwoWinState = "";
	}
	else{
		playerOneWinState = "";
		playerTwoWinState = "WINNER";
	}

	player1Text = static_cast<ui::Text*>(_rootNode->getChildByName("Text_Element_1"));
	player1Text->setString("Player 1 Score: " + StringUtils::format("%d", _leftScore) + "\n" + playerOneWinState);
	player2Text = static_cast<ui::Text*>(_rootNode->getChildByName("Text_Element_2"));
	player2Text->setString("Player 2 Score: " + StringUtils::format("%d", _rightScore) + "\n" + playerTwoWinState);
}

void Score_Scene::update(float deltaTime)
{

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