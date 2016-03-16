#include "SubPowder.h"

SubPowder* SubPowder::create()
{
	SubPowder* ball = new SubPowder();
	ball->init();
	return ball;
}

SubPowder::~SubPowder()
{

}

bool SubPowder::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("PowderBall.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->scheduleUpdate();

	return true;
}

void SubPowder::Hit(Vec2 velocity)
{
	Ball::Hit(velocity);
	_gravity = 0;
	_velocity = Vec2((_velocity.x > 0 ? 1 : -1) * Settings::horizontalSpeed, 0);
}
