#include "Player.h"
#include "Game_Scene.h"

Player* Player::create(bool onRight, BallManager* ballManager, BallDispencer* ballDispencer)
{
	Player* player = new Player();
	if (!player->init(onRight, ballManager, ballDispencer))
	{
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	player->autorelease();

	return player;
}

bool Player::init(bool onRight, BallManager* ballManager, BallDispencer* ballDispencer)
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = CSLoader::createNode("PlayerLeft.csb");
	if (onRight)
	{
		_rootNode->setScaleX(-1);
	}
	//sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	addChild(_rootNode);

	_swingButton = _rootNode->getChildByName<Button*>("Fire_Button");
	// we do not want it but we might bring it back uder a different name, like use super powerful power of awesome button
	_swingButton->setVisible(false);

	_normalSPR = _rootNode->getChildByName<Sprite*>("Sprite_1");
	_dazedSPR = _rootNode->getChildByName<Sprite*>("Sprite_2");
	auto asdf1 = Sprite::create("res/Animations/Idle/0001.png");
	_idleSprite = _rootNode->getChildByName<Sprite*>("Sprite_Idle");
	int numIdleFrames = 120;
	float idleFrameRate = 60;
	_idleFrames.reserve(numIdleFrames);
	for (int i = 1; i <= numIdleFrames; i++)
	{
		string index = to_string(i);
		//pad with '0' to length of 4
		string pad = string(4 - index.length(), '0');
		string path = "res/Animations/Idle/";
		string fileType = ".png";
		string file = path + pad + index + fileType;
		_idleFrames.pushBack(SpriteFrame::create(file, Rect(0, 0, 300, 225)));
	}
	_idleAnimation = Animation::createWithSpriteFrames(_idleFrames, 1.0f / idleFrameRate, numeric_limits<unsigned int>::max());
	//_idleSprite->runAction(Animate::create(_idleAnimation));
	//	_vDazedSPR = _rootNode->getChildByName<Sprite*>("Sprite_4");
	_dazedSPR->setVisible(false);

	//_swingButton->addTouchEventListener(CC_CALLBACK_2(Player::SwingButtonPressed, this));

	_ballManager = ballManager;
	_ballDispencer = ballDispencer;
	_score = 0;
	_dazedState = false;
	_veryDazed = false;

	_timeSinceHit = 100;//long time since last hit so dont immediately daze
	_stunLockTimer = 0;

	this->scheduleUpdate();

	return true;
}

void Player::update(float deltaTime)
{
	_ballDispencer->DisplayScore(_score);

	_timeSinceHit += deltaTime;
	_stunLockTimer += deltaTime;

	if (IsDazed())
	{
		float recoveryTime = Settings::playerDazeRecoveryTime * (_veryDazed ? 3 : 1);
		if (_timeSinceHit >= recoveryTime)
		{
			EndDaze();
		}
	}
	// How long invincible lasts for
	// If invincible is true
	if (_invincible)
	{
		// How much time has passed is added to invincibleTime
		_invincibleTime += deltaTime; 

		// If invincibleTime is greater than how long powerups last for
		if (_invincibleTime >= Settings::powerUpTime)
		{
			_invincible = false;
		}
	}

}

/*void Player::SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (!_dazedState)
	{
		if (type == ui::Widget::TouchEventType::BEGAN)
		{
			//Do super awesome undefined thing here future us
		}
	}
}*/

void Player::SwingBat()
{
	_idleSprite->stopAllActions();
	_idleAnimation = Animation::createWithSpriteFrames(_idleFrames, 1.0f / 60.0f, 100);
	_idleSprite->runAction(Animate::create(_idleAnimation));

	if (!IsDazed())
	{
		for (size_t i = 0; i < _ballManager->GetNumberOfBalls(); i++)
		{
			Ball& ball = *_ballManager->GetBallAtIndex(i);

			// don't test if ball belongs to other player
			// not enough balls to justify it.
			if (!ball.IsContained())
			{
				Vec2 ppos = this->convertToWorldSpace(Vec2());
				Vec2 bpos = ball.getParent()->convertToWorldSpace(ball.getPosition());
				Vec2 toBall = bpos - ppos;
				//float r = 100;
				float r = 150;
				if (toBall.length() < r)
				{
					if (ball.getType() == BombBall::type)
					{	
						Vec2 emptySpace; //Basically a placeholder because this will only be used in case of bomb balls, but hit requires a vec2 even if one is not used.
						ball.Hit(emptySpace);
						PlayerHitByBall(&ball);
						((Game_Scene*)(this->getParent()->getParent()))->SeeSaw(this, -Settings::playerSeeSawMoveDistance);
					}
					else if (ball.getType() == WalletBall::type)
					{
						Vec2 emptySpace; //Basically a placeholder because this will only be used in case of bomb balls, but hit requires a vec2 even if one is not used.
						ball.Hit(emptySpace);
						((Game_Scene*)(this->getParent()->getParent()))->SeeSaw(this, Settings::playerSeeSawMoveDistance);
					}
					else
					{ 
						float difficulty = 0.1f; // 0=easy, 1=hard
						float dy = toBall.y / r; // -1 -> 1
						dy = (dy > 0 ? 1 : -1) * pow(abs(cbrtf(dy)), (1.0f - difficulty)); // cubic curve, harder to get y just right
						dy = (dy + 1) / 2.0f; // 0 -> 1 for lerp
						Vec2 hitDir = ccpLerp(Vec2(Settings::horizontalSpeed, -250), Vec2(Settings::horizontalSpeed, 550), dy); // lerp between mim/max hit strength
						ball.Hit(hitDir);
					}
				}
			}
		}
	}
}

void Player::PlayerHitByBall(Ball* ball)
{
	if (!_invincible)
	{
		//get hit
		_timeSinceHit = 0.0f;
		//daze only if not dazed too recently
		if (_stunLockTimer >= Settings::playerDazeInvincibilityTime)
		{
			_stunLockTimer = 0;
			if (ball->getType() == OilBall::type || ball->getType() == BombOther::type)
			{
				Daze(true);
			}
			else
			{
				Daze();
			}
		}
		if (ball->getType() == BombOther::type)
		{
			((Game_Scene*)(this->getParent()->getParent()))->SeeSaw(this, -4);

			Explosion* boomImage;
			boomImage = Explosion::create();
			ball->getParent()->addChild(boomImage);

			boomImage->setPosition(ball->getParent()->convertToWorldSpace(ball->getPosition()));
			((Game_Scene*)(ball->getParent()->getParent()))->DestroyAndDropBall(ball);
		}
	}
}

void Player::SetInvincible()
{
	_invincible = true;

	//invincibleTime set to 0
	_invincibleTime = 0;
}

bool Player::IsInvincible()
{
	return _invincible;
}

void Player::SetDoubleAttack()
{
	_doubleAttack = true;
	_doubleAttackTime = 0;
}

void Player::Daze(bool extendedTime)
{
	_dazedState = true;
	_normalSPR->setVisible(false);
	//_swingButton->setVisible(false);
	if (extendedTime)
	{
		_veryDazed = true;
		//_vDazedSPR->setVisible(true);
		_dazedSPR->setVisible(true);
	}
	else
	{
		_dazedSPR->setVisible(true);
	}
	_idleAnimation = Animation::createWithSpriteFrames(_idleFrames, 1.0f / 60.0f, 100);
	_idleSprite->runAction(Animate::create(_idleAnimation));
}

void Player::EndDaze()
{
	_dazedState = _veryDazed = false;
	_dazedSPR->setVisible(false);
	//_vDazedSPR->setVisible(false);
	_normalSPR->setVisible(true);
	//_swingButton->setVisible(true);
}

void Player::addScore(int points)
{
	_score += points;
}

int Player::getScore()
{
	return _score;
}