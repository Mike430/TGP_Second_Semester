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
	_leftDispencer->setZOrder(1);
	for (int i = 0; i < 15; i++) _leftDispencer->AddBall();
	_ballDispencers.push_back(_leftDispencer);

	_rightDispencer = BallDispencer::create();
	_rightDispencer->Setup(true, 960, 725, _ballManager);
	_rootNode->addChild(_rightDispencer);
	_rightDispencer->setZOrder(1);
	for (int i = 0; i < 15; i++) _rightDispencer->AddBall();
	_ballDispencers.push_back(_rightDispencer);

	// For all Players
	const string path = "res/";
	const float y = 300;
	const float centerX = Director::getInstance()->getVisibleSize().width / 2;
	const float relativeX = 570;

	// Left Player
	_leftPlayer = Player::create(path + "PlayerLeft.csb", _ballManager, _leftDispencer);
	_leftPlayer->setPosition(Vec2(centerX + relativeX * -1, y));
	_rootNode->addChild(_leftPlayer);
	_players.push_back(_leftPlayer);

	// Right Player
	_rightPlayer = Player::create(path + "PlayerRight.csb", _ballManager, _rightDispencer);
	_rightPlayer->setPosition(Vec2(centerX + relativeX * 1, y));
	_rootNode->addChild(_rightPlayer);
	_players.push_back(_rightPlayer);

	// Random Generator
	srand(time(NULL));

	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	_endButton->addTouchEventListener(CC_CALLBACK_2(Game_Scene::EndButtonPressed, this));
	// Assign the event methods to the event listener (known as callbacks)
	touchListener->onTouchBegan = CC_CALLBACK_2(Game_Scene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Game_Scene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Game_Scene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Game_Scene::onTouchCancelled, this);

	_countDown = 3.0f;
	_paused = false;

	// Calls the game loop
	this->scheduleUpdate();
	// INIT ENDS IN RETURN TRUE
	return true;
}



// Game Methods
//==============================================================================
void Game_Scene::update(float deltaTime)
{
	string textDisplay = "Score: " + to_string((int)(1337));
	_scoreLabel->setText(textDisplay);

	if (_countDown <= 0 && !_paused)
	{
		// test if ball is outside and delete
		for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
		{
			Ball* subject = _ballManager->GetBallAtIndex(i);

			if ((subject->getPositionX() > _windowSize.x ||
				subject->getPositionX() < 0 ||
				subject->getPositionY() > _windowSize.y ||
				subject->getPositionY() < 0) && !subject->GetContained())
			{
				if (subject->GetLeftOrRight())
					_rightDispencer->DropBall();
				else
					_leftDispencer->DropBall();

				bool temp = !subject->GetLeftOrRight();
				_ballManager->DestroyBall(i);
				break;
			}
		}
		// if ball intersects target, get leftorRight var from ball and add to player score

		for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
		{
			Ball* ball = _ballManager->GetBallAtIndex(i);
			if (!ball->GetContained())
			{
				Rect ballBB = ball->getChildren().at(0)->getChildByName("Sprite_1")->getBoundingBox();
				ballBB.origin = ball->convertToWorldSpace(ballBB.origin);
				Player* player = ball->GetLeftOrRight() ? _leftPlayer : _rightPlayer; //only check opposite player

				Rect playerBB = player->getChildren().at(0)->getChildByName("Sprite_2")->getBoundingBox();
				playerBB.origin = player->convertToWorldSpace(playerBB.origin);

				if (playerBB.intersectsRect(ballBB))
				{
					ball->GetLeftOrRight() ? _rightDispencer->DropBall() : _leftDispencer->DropBall();
					_ballManager->DestroyBall(i);
					Player* otherPlayer = ball->GetLeftOrRight() ? _rightPlayer : _leftPlayer;
					otherPlayer->addScore(10);

					//seesaw
					float time = 0.1;
					Vec2 dPos = Vec2(0, 18);
					player->runAction(MoveBy::create(time, -dPos));
					otherPlayer->runAction(MoveBy::create(time, dPos));

					// win/lose check
					int leftScore, rightScore;
					leftScore = _leftPlayer->getScore();
					rightScore = _rightPlayer->getScore();
					int deltaScore = abs(leftScore - rightScore);

					if (deltaScore >= 100)
					{
						//someone is pretty close to the bottom of the screen
						cocos2d::Scene* scoreScene = Score_Scene::createScene(leftScore, rightScore);
						cocos2d::CCDirector::getInstance()->replaceScene(scoreScene);
					}
					break;
				}
			}
		}
	}
	else
	{
		_countDown -= deltaTime;

		if (_countDown <= 0)
		{
			_rightDispencer->DropBall();
			_leftDispencer->DropBall();
		}
	}
}



// Callbacks
//==============================================================================
void Game_Scene::EndButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	
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
