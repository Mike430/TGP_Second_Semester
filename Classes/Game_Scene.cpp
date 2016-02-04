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
	_windowSize = CCDirector::getInstance()->getVisibleSize();
	// Get Scene Elelments
	_endButton = (cocos2d::ui::Button*)_rootNode->getChildByName("End_Button");
	_scoreLabel = (cocos2d::ui::Text*)_rootNode->getChildByName("Text_Element_1");

	_ballManager = new BallManager();

	//BallDispencers
	_leftDispencer = BallDispencer::create();
	_leftDispencer->Setup(false, 320, 725, _ballManager);
	_rootNode->addChild(_leftDispencer);
	for (int i = 0; i < 15; i++) _leftDispencer->AddBall();

	_rightDispencer = BallDispencer::create();
	_rightDispencer->Setup(true, 960, 725, _ballManager);
	_rootNode->addChild(_rightDispencer);
	for (int i = 0; i < 15; i++) _rightDispencer->AddBall();

	//Players
	const string path = "res/";
	const float y = 250;
	const float centerX = Director::getInstance()->getVisibleSize().width / 2;
	const float relativeX = 500;

	for (const auto& p : vector<pair<string, Vec2>>{ { "PlayerLeft.csb", { -1, 0 } }, { "PlayerRight.csb", { 1, 0 } } })
	{
		Player& player = *Player::create(path + p.first, _ballManager);
		player.setPosition(Vec2(centerX + relativeX * p.second.x, y));
		_players.push_back(&player);
		_rootNode->addChild(&player);
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

	for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
	{
		Ball* subject = _ballManager->GetBallAtIndex(i);

		if ((subject->getPositionX() > _windowSize.x ||
			subject->getPositionX() < 0 ||
			subject->getPositionY() > _windowSize.y ||
			subject->getPositionY() < 0) && !subject->GetContained())
		{
			bool temp = subject->GetLeftOrRight();
			_ballManager->DestroyBall(i);

			BallDispencer* dispencer = (temp ? _leftDispencer : _rightDispencer);
			dispencer->AddBall();
			break;
		}
	}
	// test if ball is outside and delete but also get leftOrRight bool - call ball manager (pointer to ball call ball's->getLeftOrRight)
	// if ball deleted, tell left or right ball dispencer to make new one - ball disoencer calls ball manager
	// 
	// if ball intersects target, get leftorRight var from ball and add to player score
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
