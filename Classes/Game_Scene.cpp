#include "Game_Scene.h"
#include "Invincibility.h"
#include "Double_Attack.h"

// Initialisers
//==============================================================================
cocos2d::Scene* Game_Scene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();
	// 'layer' is an autorelease object
	auto layer = Game_Scene::create();
	// add layer as a child to scene
	scene->addChild(layer, 0, "Game_Scene");
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

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("res/Audio/mainsong.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);

	// Random Generator
	srand(time(NULL));
	// Scene Setter
	_rootNode = cocos2d::CSLoader::createNode("1_Game_Scene.csb");
	this->addChild(_rootNode);
	_windowSize = CCDirector::getInstance()->getVisibleSize();
	// Get Scene Elelments
	_scoreLabel = (cocos2d::ui::Text*)_rootNode->getChildByName("Text_Element_1");

	_ballManager = new BallManager();
	_targetManager = new TargetManager();
	_gameProgression = new GameProgression(this);

	//BallDispencers
	_leftDispencer = BallDispencer::create();
	_leftDispencer->Setup(false, 320, 725, _ballManager);
	_rootNode->addChild(_leftDispencer);
	_leftDispencer->setLocalZOrder(1);
	_ballDispencers.push_back(_leftDispencer);

	_rightDispencer = BallDispencer::create();
	_rightDispencer->Setup(true, 960, 725, _ballManager);
	_rootNode->addChild(_rightDispencer);
	_rightDispencer->setLocalZOrder(1);
	_ballDispencers.push_back(_rightDispencer);

	for (int i = 0; i < 15; i++)
	{
		_leftDispencer->AddBall();
		_rightDispencer->AddBall();
	}

	// For all Players
	const string path = "res/";
	const float centerX = Director::getInstance()->getVisibleSize().width / 2;
	Vec2 playerStartPos = Vec2(centerX, Settings::playerStartY);

	// Left Player
	_leftPlayer = Player::create(false, _ballManager, _leftDispencer);
	_leftPlayer->setPosition(playerStartPos - Vec2(Settings::playerRelativeStartX, 0));
	_rootNode->addChild(_leftPlayer);
	_players.push_back(_leftPlayer);

	// Right Player
	_rightPlayer = Player::create(true, _ballManager, _rightDispencer);
	_rightPlayer->setPosition(playerStartPos + Vec2(Settings::playerRelativeStartX, 0));
	_rootNode->addChild(_rightPlayer);
	_players.push_back(_rightPlayer);


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
	_unPauseButton = _rootNode->getChildByName<Button*>("btn_unpause");
	_unPauseButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			UnPause();
		}
	});
	_unPauseButton->setVisible(false);

	_targets.reserve(10);
	_targetSpawnTimer = Settings::targetMinSpawnDelay;

	// Calls the game loop
	this->scheduleUpdate();
	// INIT ENDS IN RETURN TRUE
	return true;
}



// Game Methods
//==============================================================================
void Game_Scene::update(float deltaTime)
{
	if (_paused)
	{
		return;
	}
	float backgroundVolume = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	if (backgroundVolume < 1.0f)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(min(1.0f, backgroundVolume + 0.3f * deltaTime));
	}
	//string textDisplay = "Score: " + to_string((int)(1337));
	//_scoreLabel->setText(textDisplay);
	// add targets outside start countdown check
	_targetSpawnTimer -= deltaTime;
	if (_targets.size() < 5)
	{
		if (_targetSpawnTimer <= 0)
		{
			if (_countDown > 0)//if game not started yet
			{
				_targetSpawnTimer = 0.5f;
			}
			else
			{
				_targetSpawnTimer = RandomHelper::random_real(Settings::targetMinSpawnDelay, Settings::targetMaxSpawnDelay);
			}
			//make a new target
			Target* newTarget = nullptr;

			newTarget = _targetManager->CreateTarget();
			
			_targets.push_back(newTarget);
			_rootNode->addChild(newTarget);
		}
	}

	if (_countDown <= 0)
	{
		_gameProgression->Update(deltaTime);
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
		// remove targets
		for (int i = 0; i < _targets.size(); i++)
		{
			if (_targets[i]->IsLifeTimeOver())
			{
				_rootNode->removeChild(_targets[i]);
				_targets.erase(_targets.begin() + i);
				break;
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

		static bool playedAirhorns = false;
		if (_countDown <= 7 && !playedAirhorns)
		{
			AudioHelper::Play("airhorn");
			playedAirhorns = true;
		}

		if (_countDown <= 0)
		{
			_rightDispencer->DropBall();
			_leftDispencer->DropBall();
		}
	}

	// turning off zero gravity after set amount of time
	if (_ballManager->GetBallAtIndex(0)->ZeroGravityField)
	{
		_NoGravTimer -= deltaTime;
		if (_NoGravTimer <= 0)
		{
			for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
			{
				_ballManager->GetBallAtIndex(i)->ZeroGravityField = false;

			}
			_NoGravTimer = Settings::ZeroGravityFieldDuration;
			AudioHelper::Play("endgrav");
		}
	}

	// turning off half gravity
	if (_ballManager->GetBallAtIndex(0)->HalfGravityField)
	{
		_HalfGravTimer -= deltaTime;
		if (_HalfGravTimer <= 0)
		{
			for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
			{
				_ballManager->GetBallAtIndex(i)->HalfGravityField = false;
			}
			_HalfGravTimer = Settings::HalfGravityFieldDuration;
			AudioHelper::Play("endgrav");
		}
	}


	// turning off double gravity
	if (_ballManager->GetBallAtIndex(0)->DoubleGravityField)
	{
		_DoubleGravTimer -= deltaTime;
		if (_DoubleGravTimer <= 0)
		{
			for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
			{
				_ballManager->GetBallAtIndex(i)->DoubleGravityField = false;
			}
			_DoubleGravTimer = Settings::DoubleGravityFieldDuration;
			AudioHelper::Play("endgrav");
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
	Rect playerRect = player->GetCollision();
	playerRect.origin = player->convertToWorldSpace(playerRect.origin);

	if (playerRect.intersectsRect(ballRect)){
		player->PlayerHitByBall(this, ball);
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

		target->Hit(this, ball);
		_targets.erase(find(_targets.begin(), _targets.end(), target));
		_rootNode->removeChild(target);

		if (ball->getType() == PowderBall::type)
		{
			PowderBallActivate(ball);
			AudioHelper::PlayRandom("powderball", 2);
		}
		else if (ball->getType() == RocketBall::type)
		{
			AudioHelper::Play("missilehit");
		}
		DestroyAndDropBall(ball);

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
	// Double Attack
	bool doubleAttack = false;

	// If leftPlayer has double attack power up
	if (player == _leftPlayer)
	{
		if (_rightPlayer->HasDoubleAttack())
		{
			doubleAttack = true;
		}

	}

	// If rightPlayer has double attack
	else if (player == _rightPlayer)
	{
		if (_leftPlayer->HasDoubleAttack())
		{
			doubleAttack = true;
		}
	}

	// If player is invincible
	if (!player->IsInvincible() || amount > 0)
	{
		float time = 0.1f;

		if (doubleAttack == true)
		{
			Vec2 changeInPos(0, Settings::playerSeeSawMoveDistance * amount * 2);
			player->runAction(MoveBy::create(time, changeInPos));
		}

		else
		{
			Vec2 changeInPos(0, Settings::playerSeeSawMoveDistance * amount);
			player->runAction(MoveBy::create(time, changeInPos));
		}

	}
}

void Game_Scene::DestroyAndDropBall(Ball* ball)
{
	if (Settings::dropRate == -1 && ball->getType() != SubPowder::type)
	{
		(ball->IsOnRight() ? _rightDispencer : _leftDispencer)->DropBall();
	}
	_ballManager->DestroyBall(ball);
}

Player* Game_Scene::GetBallHitter(Ball* ball)
{
	return ball->IsOnRight() ? _rightPlayer : _leftPlayer;
}

void Game_Scene::EndGame(int player1Score, int player2Score)
{
	cocos2d::Scene* scoreScene = Score_Scene::createScene(player1Score, player2Score);
	cocos2d::CCDirector::getInstance()->replaceScene(scoreScene);
}


void Game_Scene::PowderBallActivate(Ball* ball)
{
	for (int i = 0; i < Settings::powderClusters; i++)
	{
		SubPowder* miniCluster;
		miniCluster = SubPowder::create();

		miniCluster->Setup(ball->getParent()->convertToWorldSpace(ball->getPosition()), ball->IsOnRight());		
		miniCluster->Hit(Vec2 (RandomHelper::random_real(-600.0f, 600.0f), RandomHelper::random_real(-600.0f, 600.0f)));

		_ballManager->AddBall(_rootNode, miniCluster);
	}
	AudioHelper::Play("powderball");
}

// Callbacks
//==============================================================================
/*void Game_Scene::EndButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	
}*/

bool Game_Scene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (_paused)
	{
		return false;
	}

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

void Game_Scene::EnableUpdates(bool update)
{
	auto setUpdate = [&](Node* node)
	{
		update ? node->scheduleUpdate() : node->unscheduleUpdate();
		update ? node->resumeSchedulerAndActions() : node->stopAllActions();
	};
	for (Node* obj : vector<Node*>{ this, _leftPlayer, _rightPlayer })
	{
		setUpdate(obj);
	}
	for (int i = 0; i < _ballManager->GetNumberOfBalls(); i++)
	{
		setUpdate(_ballManager->GetBallAtIndex(i));
	}
}

void Game_Scene::Pause()
{
	_paused = true;
	_unPauseButton->setVisible(true);
	EnableUpdates(false);
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void Game_Scene::UnPause()
{
	_paused = false;
	_unPauseButton->setVisible(false);
	EnableUpdates(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}

bool Game_Scene::IsPaused()
{
	return _paused;
}
