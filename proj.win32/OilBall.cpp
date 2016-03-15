#include "OilBall.h"

OilBall* OilBall::create()
{
	OilBall* ball = new OilBall();
	ball->init();
	return ball;
}

OilBall::~OilBall()
{

}

bool OilBall::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("OilBall.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->_type = 1;
	this->scheduleUpdate();

	return true;
}

void OilBall::Hit(Vec2 velocity)
{
	Ball::Hit(velocity);
	_gravity = 0;
	_velocity = Vec2((_velocity.x > 0 ? 1 : -1) * Settings::horizontalSpeed, 0);
}
