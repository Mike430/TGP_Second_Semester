#include "Player.h"

Player* Player::create(const string csbFile, BallManager* ballManager)
{
	Player* player = new Player();
	if (!player->init(csbFile, ballManager))
	{
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	player->autorelease();

	return player;
}

bool Player::init(const string csbFile, BallManager* ballManager)
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = CSLoader::createNode(csbFile);
	//sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	addChild(_rootNode);

	_swingButton = _rootNode->getChildByName<Button*>("Fire_Button");
	_swingButton->addTouchEventListener(CC_CALLBACK_2(Player::SwingButtonPressed, this));

	_ballManager = ballManager;

	this->scheduleUpdate();

	return true;
}

void Player::update(float delta)
{
	
}

void Player::SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		for (size_t i = 0; i < _ballManager->GetNumberOfBalls(); i++)
		{
			Ball& ball = *_ballManager->GetBallAtIndex(i);
			Vec2 ppos = this->convertToWorldSpace(Vec2());
			Vec2 bpos = ball.getParent()->convertToWorldSpace(ball.getPosition());
			Vec2 toBall = bpos - ppos;
			float r = 100;
			if (toBall.length() < r)
			{
				float difficulty = 0.1f; // 0=easy, 1=hard
				float dy = toBall.y / r; // -1 -> 1
				dy = (dy > 0 ? 1 : -1) * pow(abs(cbrtf(dy)), (1.0f - difficulty)); // cubic curve, harder to get y just right
				dy = (dy + 1) / 2.0f; // 0 -> 1 for lerp
				Vec2 hitDir = ccpLerp(Vec2(1200, -250), Vec2(1200, 550), dy); // lerp between mim/max hit strength
				ball.Hit(hitDir);
			}
		}
	}
}