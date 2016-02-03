#include "Game_Scene.h"

// Initialisers
//==============================================================================
cocos2d::Scene* Game_Scene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();
	// 'layer' is an autorelease object
	auto layer = Game_Scene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	//RETURN
	return scene;
}

bool Game_Scene::init()
{
	// A call to super? C++ doesn't have one so this is needed.
	if (!Layer::init())
	{
		return false;
	}

	// Scene Setter
	_rootNode = cocos2d::CSLoader::createNode("1_Game_Scene.csb");
	this->addChild(_rootNode);
	// Get Scene Elelments
	_endButton = (cocos2d::ui::Button*)_rootNode->getChildByName("End_Button");
	_scoreLabel = (cocos2d::ui::Text*)_rootNode->getChildByName("Text_Element_1");

	//BallDispencers
	_leftDispencer = BallDispencer::create();
	_leftDispencer->Setup(false, 320, 725);
	_rootNode->addChild(_leftDispencer);

	_rightDispencer = BallDispencer::create();
	_rightDispencer->Setup(true, 960, 725);
	_rootNode->addChild(_rightDispencer);

	//Setup Game Elements
	_testBall1 = Ball::create();
	_testBall1->Setup(200.0f, 600.0f, 20.0f);
	_rootNode->addChild(_testBall1);
	_testBall2 = Ball::create();
	_testBall2->Setup(500.0f, 500.0f, 10.0f);
	_rootNode->addChild(_testBall2);
	_testBall3 = Ball::create();
	_testBall3->Setup(800.0f, 400.0f, 10.0f);
	_rootNode->addChild(_testBall3);

	//Players
	const string path = "res/";
	const float y = 250;
	const float centerX = Director::getInstance()->getVisibleSize().width / 2;
	const float relativeX = 500;
	for (const auto& p : vector<pair<string, Vec2>>{ { "PlayerLeft.csb", { -1, 0 } }, { "PlayerRight.csb", { 1, 0 } } })
	{
		_players.push_back(Player::create(path + p.first, Vec2(centerX + relativeX * p.second.x, y)));
		_rootNode->addChild(_players.back());
	}

	// Random Generator
	srand(time(NULL));

	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	_endButton->addTouchEventListener(CC_CALLBACK_2(Game_Scene::EndButtonPressed, this));
	// Assign the event methods to the event listener (known as callbacks)
	touchListener->onTouchBegan = CC_CALLBACK_2(Game_Scene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Game_Scene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Game_Scene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Game_Scene::onTouchCancelled, this);

	// Calls the game loop
	this->scheduleUpdate();
	// INIT ENDS IN RETURN TRUE
	return true;
}



// Game Methods
//==============================================================================
void Game_Scene::update(float deltaTime)
{
	string textDisplay = "Score: " + to_string((int) (1337));
	_scoreLabel->setText(textDisplay);
}



// Callbacks
//==============================================================================
void Game_Scene::EndButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	cocos2d::Scene* scoreScene = Score_Scene::createScene();
	cocos2d::CCDirector::getInstance()->replaceScene(scoreScene);
}

bool Game_Scene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void Game_Scene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void Game_Scene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void Game_Scene::onTouhCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{
}
