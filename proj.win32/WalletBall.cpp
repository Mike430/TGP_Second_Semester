#include "WalletBall.h"

WalletBall* WalletBall::create()
{
	WalletBall* ball = new WalletBall();
	ball->init();
	return ball;
}

WalletBall::~WalletBall()
{

}

bool WalletBall::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("WalletBall.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->_type = 1;
	this->scheduleUpdate();

	return true;
}

void WalletBall::Hit(Vec2 velocity)
{
	Ball::Hit(velocity);
	_gravity = 0;
	_velocity = Vec2((_velocity.x > 0 ? 1 : -1) * Settings::horizontalSpeed, 0);
}
