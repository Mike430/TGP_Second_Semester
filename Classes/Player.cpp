#include "Player.h"

Player* Player::create(const string csbFile, const Vec2 position)
{
	Player* player = new Player();
	if (!player->init(csbFile, position))
	{
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	player->autorelease();

	return player;
}

bool Player::init(const string csbFile, const Vec2 position)
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = CSLoader::createNode(csbFile);
	//sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	addChild(_rootNode);
	setPosition(position);

	_swingButton = _rootNode->getChildByName<Button*>("Fire_Button");
	_swingButton->addTouchEventListener(CC_CALLBACK_2(Player::SwingButtonPressed, this));

	this->scheduleUpdate();

	return true;
}

void Player::update(float delta)
{
	
}

void Player::SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	//vector<Ball>& balls = 
}