#include "Player.h"

Player* Player::create(const string csbFile, BallManager* ballManager, BallDispencer* ballDispencer)
{
	Player* player = new Player();
	if (!player->init(csbFile, ballManager, ballDispencer))
	{
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	player->autorelease();

	return player;
}

bool Player::init(const string csbFile, BallManager* ballManager, BallDispencer* ballDispencer)
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = CSLoader::createNode(csbFile);
	//sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	addChild(_rootNode);

	_swingButton = _rootNode->getChildByName<Button*>("Fire_Button");
	// we do not want it but we might bring it back uder a different name, like use super powerful power of awesome button
	_swingButton->setVisible(false);

	_normalSPR = _rootNode->getChildByName<Sprite*>("Sprite_1");
	_dazedSPR = _rootNode->getChildByName<Sprite*>("Sprite_2");
	_dazedSPR->setVisible(false);

	//_swingButton->addTouchEventListener(CC_CALLBACK_2(Player::SwingButtonPressed, this));

	_ballManager = ballManager;
	_ballDispencer = ballDispencer;
	_score = 0;
	_dazedState = false;

	this->scheduleUpdate();

	return true;
}

void Player::update(float deltaTime)
{
	_ballDispencer->DisplayScore(_score);
	if (_dazedState)
	{
		_timeOut += deltaTime;
		if (_timeOut >= _recoveryTime)
		{
			_dazedState = false;
			//_swingButton->setVisible(true);
			_normalSPR->setVisible(true);
			_dazedSPR->setVisible(false);
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
			_invincibleTime = false;
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
	if (!_dazedState)
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

void Player::PlayerHitByBall()
{
	if (!_invincible)
	{
		_timeOut = 0.0f;
		_dazedState = true;
		//_swingButton->setVisible(false);
		_normalSPR->setVisible(false);
		_dazedSPR->setVisible(true);
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

void Player::addScore(int points)
{
	_score += points;
}

int Player::getScore()
{
	return _score;
}