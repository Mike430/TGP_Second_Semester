#include "PowderBall.h"

PowderBall* PowderBall::create()
{
	PowderBall* ball = new PowderBall();
	ball->init();
	return ball;
	
}

PowderBall::~PowderBall()
{

}

bool PowderBall::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->_type = 2; // set type of ball
	this->_rootNode = cocos2d::CSLoader::createNode("PowderBall.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");
	this->scheduleUpdate();

	return true;
}

/**
void PowderBall::Hit(Vec2 velocity)
{
	Ball::Hit(velocity);
	_gravity = 0;
	_velocity = Vec2((_velocity.x > 0 ? 1 : -1) * Settings::horizontalSpeed, 0);
}*/