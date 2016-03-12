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
	_leftDispencer->setLocalZOrder(1);
	for (int i = 0; i < 15; i++) _leftDispencer->AddBall();
	_ballDispencers.push_back(_leftDispencer);

	_rightDispencer = BallDispencer::create();
	_rightDispencer->Setup(true, 960, 725, _ballManager);
	_rootNode->addChild(_rightDispencer);
	_rightDispencer->setLocalZOrder(1);
	for (int i = 0; i < 15; i++) _rightDispencer->AddBall();
	_ballDispencers.push_back(_rightDispencer);

	// For all Players
	const string path = "res/";
	const float centerX = Director::getInstance()->getVisibleSize().width / 2;
	Vec2 playerStartPos = Vec2(centerX, Settings::playerStartY);

	// Left Player
	_leftPlayer = Player::create(path + "PlayerLeft.csb", _ballManager, _leftDispencer);
	_leftPlayer->setPosition(playerStartPos - Vec2(Settings::playerRelativeStartX, 0));
	_rootNode->addChild(_leftPlayer);
	_players.push_back(_leftPlayer);

	// Right Player
	_rightPlayer = Player::create(path + "PlayerRight.csb", _ballManager, _rightDispencer);
	_rightPlayer->setPosition(playerStartPos + Vec2(Settings::playerRelativeStartX, 0));
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

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	_countDown = 3.0f;
	_paused = false;

	_targets.reserve(10);

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

			if (!ball->IsContained())
			{
				if (TestIfBallIsOut(ball))
				{
					break;
				}

				if (ball->IsCollidable())
				{
					bool targetCollision = false;
					for (Target* target : _targets)
					{
						if (TestCollisionWithTarget(ball, target))
						{
							targetCollision = true;
							break;
						}
					}
					if (targetCollision)
					{
						break;
					}

					if (TestCollisionWithPlayer(ball))
					{
						break;
					}
				}
			}
		}
		// add targets
		if (_targets.size() < 5)
		{
			if (rand_0_1() < 0.5 / 60.0)//about every couple seconds
			{
				//make a new target
				if (rand_0_1() < 1.0 / 6.0 && false)
				{
					//make a fancy new target that does something
				}
				else
				{
					//make a normal target
					bool common = rand_0_1() < 0.9;
					int numRare = 0;
					for (Target* target : _targets)
					{
						RareTarget* rare = dynamic_cast<RareTarget*>(target);
						if (rare) numRare++;
					}
					if (numRare >= 2)
					{
						common = true;
					}
					Target* newTarget = (common ? (Target*)CommonTarget::create() : (Target*)RareTarget::create());
					_targets.push_back(newTarget);
					_rootNode->addChild(newTarget);
				}
			}
		}
		// win/lose check
		for (auto& player : _players)
		{
			if (player->getPositionY() < Settings::playerMinY || player->getPositionY() > Settings::playerMaxY)
			{
				EndGame(_leftPlayer->getScore(), _rightPlayer->getScore());
				break;
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

bool Game_Scene::TestCollisionWithPlayer(Ball* ball)
{
	// make a hit box to represent the ball
	Rect ballRect = ball->getChildren().at(0)->getChildByName("Sprite_1")->getBoundingBox();
	ballRect.origin = ball->convertToWorldSpace(ballRect.origin);

	// Get the ball owner's opposing player
	Player* player = ball->IsOnRight() ? _leftPlayer : _rightPlayer;

	// make a hit box to represent the opponent
	Rect playerRect = player->getChildren().at(0)->getChildByName("Sprite_2")->getBoundingBox();
	playerRect.origin = player->convertToWorldSpace(playerRect.origin);

	if (playerRect.intersectsRect(ballRect)){
		player->PlayerHitByBall();
		SeeSaw(player, -1);
		ball->SetCollidable(false);
		return true;
	}
	return false;
}

bool Game_Scene::TestCollisionWithTarget(Ball* ball, Target* target)
{
	Rect targetRect;
	targetRect = target->GetCollision();
	targetRect.origin = target->convertToWorldSpace(targetRect.origin);

	Rect ballRect;
	ballRect = ball->getChildren().at(0)->getChildByName("Sprite_1")->getBoundingBox();
	ballRect.origin = ball->convertToWorldSpace(ballRect.origin);

	if (ballRect.intersectsRect(targetRect))
	{
		int score = target->GetScoreValue();

		// Get the ball's owner
		Player* playerWin = ball->IsOnRight() ? _rightPlayer : _leftPlayer;
		// Get the opposition
		Player* playerLose = ball->IsOnRight() ? _leftPlayer : _rightPlayer;

		SeeSaw(playerWin, 1);
		SeeSaw(playerLose, -1);
		playerWin->addScore(score);

		DestroyAndDropBall(ball);

		target->Hit(this);
		_targets.erase(find(_targets.begin(), _targets.end(), target));
		_rootNode->removeChild(target);

		return true;
	}

	return false;
}

bool Game_Scene::TestIfBallIsOut(Ball* ball)
{
	if ((ball->getPositionX() > _windowSize.x
		|| ball->getPositionX() < 0
		|| ball->getPositionY() > _windowSize.y
		|| ball->getPositionY() < 0))
	{
		DestroyAndDropBall(ball);
		return true;
	}
	return false;
}

void Game_Scene::SeeSaw(Player* player, int amount)
{
	float time = 0.1;
	Vec2 dPos(0, Settings::playerSeeSawMoveDistance * amount);
	player->runAction(MoveBy::create(time, dPos));
}

void Game_Scene::DestroyAndDropBall(Ball* ball)
{
	if (Settings::dropRate == -1)
	{
		(ball->IsOnRight() ? _rightDispencer : _leftDispencer)->DropBall();
	}
	_ballManager->DestroyBall(ball);
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
	if (touch->getLocation().x > (_windowSize.x / 2))
		_rightPlayer->SwingBat();
	else
		_leftPlayer->SwingBat();

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
