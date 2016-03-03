#include "RocketBall.h"

RocketBall* RocketBall::create()
{
	RocketBall* ball = new RocketBall();
	ball->init();
	return ball;
}

RocketBall::~RocketBall()
{
	
}

bool RocketBall::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("RocketBall.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");
	this->scheduleUpdate();

	return true;
}

void RocketBall::Hit(Vec2 velocity)
{
	Ball::Hit(velocity);
	_gravity = 0;
	_velocity = Vec2((_velocity.x > 0 ? 1 : -1) * Settings::horizontalSpeed, 0);
}
