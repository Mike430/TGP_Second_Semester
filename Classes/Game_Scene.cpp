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
	const float relativeX = 530;

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
	//_endButton->addTouchEventListener(CC_CALLBACK_2(Game_Scene::EndButtonPressed, this));
	// Assign the event methods to the event listener (known as callbacks)
	touchListener->onTouchBegan = CC_CALLBACK_2(Game_Scene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Game_Scene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Game_Scene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Game_Scene::onTouchCancelled, this);

	for (int i = 0; i < _numbOfTargets; i++)
	{
		_targets[i] = Target::create();
		_targets[i]->setZOrder(2);
		_rootNode->addChild(_targets[i]);
	}

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
	//string textDisplay = "Score: " + to_string((int)(1337));
	//_scoreLabel->setText(textDisplay);

	if (_countDown <= 0 && !_paused)
	{
		// if ball intersects target, get leftorRight var from ball and add to player score
		for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
		{
			Ball* ball = _ballManager->GetBallAtIndex(i);

			if (!ball->GetContained())
			{
				TestIfBallIsOut(ball, i);

				for (int j = 0; j < _numbOfTargets; j++)
				{
					if (_targets[j]->GetActive())
						TestCollisionWithTargets(ball, i, j);
				}

				if (TestCollisionWithPlayer(ball, i))
				{
					int leftScore = _leftPlayer->getScore();
					int rightScore = _rightPlayer->getScore();

					EndGame(leftScore, rightScore);
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

bool Game_Scene::TestCollisionWithPlayer(Ball* ball, int ballIndex)
{
	// make a hit box to represent the ball
	Rect ballRect = ball->getChildren().at(0)->getChildByName("Sprite_1")->getBoundingBox();
	ballRect.origin = ball->convertToWorldSpace(ballRect.origin);

	// Get the ball owner's opposing player
	Player* player = ball->GetLeftOrRight() ? _leftPlayer : _rightPlayer;

	// make a hit box to represent the opponent
	Rect playerRect = player->getChildren().at(0)->getChildByName("Sprite_2")->getBoundingBox();
	playerRect.origin = player->convertToWorldSpace(playerRect.origin);

	if (playerRect.intersectsRect(ballRect))
	{
		player->PlayerHit();
		ball->GetLeftOrRight() ? _rightDispencer->DropBall() : _leftDispencer->DropBall();
		_ballManager->DestroyBall(ballIndex);
		Player* otherPlayer = ball->GetLeftOrRight() ? _rightPlayer : _leftPlayer;
		otherPlayer->addScore(10);

		SeeSaw(otherPlayer, player);

		// win/lose check
		int leftScore, rightScore;
		leftScore = _leftPlayer->getScore();
		rightScore = _rightPlayer->getScore();
		int deltaScore = abs(leftScore - rightScore);

		if (deltaScore >= 100)
			return true;
		else
			return false;

	}
	else
		return false;
}

bool Game_Scene::TestCollisionWithTargets(Ball* ball, int ballIndex, int targetIndex)
{
	Rect targetRect;
	//targetRect = _targets[targetIndex]->getChildByName("common_Sprite")->getBoundingBox();
	targetRect = _targets[targetIndex]->getChildren().at(0)->getChildByName("common_Sprite")->getBoundingBox();

	Rect ballRect;
	ballRect = ball->getChildren().at(0)->getChildByName("Sprite_1")->getBoundingBox();

	if (targetRect.intersectsRect(ballRect))
	{
		int score;
		score = _targets[targetIndex]->GetScarcity() ? 5 : 20;
		ball->GetLeftOrRight() ? _rightDispencer->DropBall() : _leftDispencer->DropBall();

		// Get the ball's owner
		Player* playerWin = ball->GetLeftOrRight() ? _rightPlayer : _leftPlayer;
		// Get the opposition
		Player* playerLose = ball->GetLeftOrRight() ? _leftPlayer : _rightPlayer;

		SeeSaw(playerWin, playerLose);

		_ballManager->DestroyBall(ballIndex);
		_targets[targetIndex]->Hit();

	}

	return true;
}

void Game_Scene::TestIfBallIsOut(Ball* ball, int ballIndex)
{
	if ((ball->getPositionX() > _windowSize.x ||
		ball->getPositionX() < 0 ||
		ball->getPositionY() > _windowSize.y ||
		ball->getPositionY() < 0) && !ball->GetContained())
	{
		if (ball->GetLeftOrRight())
			_rightDispencer->DropBall();
		else
			_leftDispencer->DropBall();

		bool temp = !ball->GetLeftOrRight();
		_ballManager->DestroyBall(ballIndex);
	}
}

void Game_Scene::SeeSaw(Player* winningPlayer, Player* loosingPlayer)
{
	float time = 0.1;
	Vec2 dPos = Vec2(0, 18);
	winningPlayer->runAction(MoveBy::create(time, dPos));
	loosingPlayer->runAction(MoveBy::create(time, -dPos));
}

void Game_Scene::EndGame(int player1Score, int player2Score)
{
	cocos2d::Scene* scoreScene = Score_Scene::createScene(player1Score, player2Score);
	cocos2d::CCDirector::getInstance()->replaceScene(scoreScene);
}



// Callbacks
//==============================================================================
/*void Game_Scene::EndButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	
}*/

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
