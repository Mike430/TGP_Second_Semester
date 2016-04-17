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


	_sprite = _rootNode->getChildByName<Sprite*>("Sprite");
	_collisionSprite = _rootNode->getChildByName<Sprite*>("CollisionSprite");
	_collisionSprite->setVisible(false);
	AnimationHelper::PreLoadAnimation("Idle", 120, 300, 225);
	AnimationHelper::PreLoadAnimation("Dazed", 120, 300, 225);
	//make swing animation last exactly Settings::playerSwingDuration
	int swingFrames = 30;
	float swingFPS = (float)swingFrames / Settings::playerSwingDuration;
	AnimationHelper::PreLoadAnimation("Swing", swingFrames, 300, 225, swingFPS);

	//_swingButton->addTouchEventListener(CC_CALLBACK_2(Player::SwingButtonPressed, this));

	_ballManager = ballManager;
	_ballDispencer = ballDispencer;
	_score = 0;
	_dazedState = false;
	_veryDazed = false;

	_timeSinceHit = 100;//long time since last hit so dont immediately daze
	_stunLockTimer = 0;
	_swingCooldownTimer = 0;
	_swingHasHitYet = false;

	this->scheduleUpdate();

	return true;
}

void Player::update(float deltaTime)
{
	stringstream message;
	if (_doubleAttack)
	{
		message << "Power*2";
	}
	if (_invincible)
	{
		message << "Invincible";
	}
	_ballDispencer->DisplayText(message.str());

	_timeSinceHit += deltaTime;
	_stunLockTimer += deltaTime;
	_swingCooldownTimer += deltaTime;

	if (AnimationHelper::AnimationFinished(_sprite))
	{
		AnimationHelper::Animate(_sprite, "Idle");
	}

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
	if (_doubleAttack)
	{
		_doubleAttackTime += deltaTime;

		if (_doubleAttackTime >= Settings::powerUpTime)
		{
			_doubleAttack = false;
		}
	}

	if (!IsDazed())
	{
		//if mid swing
		if (_swingCooldownTimer <= Settings::playerSwingDuration)
		{
			if (!_swingHasHitYet)
			{
				if (_swingCooldownTimer >= Settings::playerSwingHitDelay)
				{
					HitBall();
					_swingHasHitYet = true;
				}
			}
		}
	}
}

void Player::SwingBat()
{
	if (!IsDazed() && _swingCooldownTimer >= Settings::playerSwingDuration)
	{
		_swingCooldownTimer = 0;
		_swingHasHitYet = false;
		AnimationHelper::Animate(_sprite, "Swing");
	}
}

void Player::HitBall()
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
				float r = 100;
				if (toBall.length() < r)
				{
					if (ball.getType() == BombBall::type)
					{	
						Vec2 emptySpace; //Basically a placeholder because this will only be used in case of bomb balls, but hit requires a vec2 even if one is not used.
						ball.Hit(emptySpace);
						PlayerHitByBall(nullptr, &ball);
						((Game_Scene*)(this->getParent()->getParent()))->SeeSaw(this, -4);
						AudioHelper::Play("selfexplode");
					}
					else if (ball.getType() == WalletBall::type)
					{
						Vec2 emptySpace; //Basically a placeholder because this will only be used in case of bomb balls, but hit requires a vec2 even if one is not used.
						ball.Hit(emptySpace);
						((Game_Scene*)(this->getParent()->getParent()))->SeeSaw(this, 4);
						AudioHelper::Play("moneyball");
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
					AudioHelper::PlayRandom("bathitting", 4, 0.75 + rand_0_1() * 0.5);
				}
			}
		}
	}

void Player::PlayerHitByBall(Game_Scene* game, Ball* ball)
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
			else if (ball->getType() == BombBall::type)
			{
				Daze(true);
			}
			else if (game->GetBallHitter(ball)->HasDoubleAttack())
			{
				Daze(true);
			}
			else
			{
				Daze(false);
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

			AudioHelper::Play("bombball");
		}
		else if (ball->getType() == OilBall::type)
		{
			AudioHelper::Play("oilball");
		}
		else if (ball->getType() == RocketBall::type)
		{
			AudioHelper::Play("missilehit");
		}
		AudioHelper::PlayRandom("Au", 8, (0.5 + rand_0_1() * 1.5));
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

Rect Player::GetCollision()
{
	return _collisionSprite->getBoundingBox();
}

bool Player::HasDoubleAttack()
{
	return _doubleAttack;
}

void Player::Daze(bool extendedTime)
{
	_dazedState = true;
	//_swingButton->setVisible(false);
	_veryDazed = extendedTime;
	AnimationHelper::Animate(_sprite, "Dazed", true);
}

void Player::EndDaze()
{
	_dazedState = _veryDazed = false;
	//_swingButton->setVisible(true);
	AnimationHelper::Animate(_sprite, "Idle");
}

void Player::addScore(int points)
{
	_score += points;
}

int Player::getScore()
{
	return _score;
}