#include "ZeroGravityBall.h"

ZeroGravityBall* ZeroGravityBall::createZeroGravity()
{
	ZeroGravityBall* ball = new ZeroGravityBall();
	ball->init();
	return ball;
}

ZeroGravityBall::~ZeroGravityBall()
{
	
}

bool ZeroGravityBall::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("Ball.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");
	this->scheduleUpdate();

	return true;
}

void ZeroGravityBall::Setup(Vec2 startPoint, Vec2 next, bool onRight)
{
	Ball::Setup(startPoint, next, onRight);
}

void ZeroGravityBall::Hit(Vec2 velocity)
{
	Ball::Hit(velocity);
	_gravity = 0;
}
