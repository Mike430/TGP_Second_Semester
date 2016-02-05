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
	for (size_t i = 0; i < _ballManager->GetNumberOfBalls(); i++)
	{
		Ball& ball = *_ballManager->GetBallAtIndex(i);
		Vec2 ppos = this->convertToWorldSpace(Vec2());
		Vec2 bpos = ball.getParent()->convertToWorldSpace(ball.getPosition());
		Vec2 toBall = bpos - ppos;
		if (toBall.lengthSquared() < 1000 * 1000)
		{
			ball.Hit(toBall);
		}
	}
}