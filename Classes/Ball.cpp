#include "Ball.h"


Ball* Ball::create()
{
	Ball* newBall = new Ball();
	newBall->init();
	return newBall;
}

bool Ball::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("Ball.csb");
	this->addChild(_rootNode);
	_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");
	this->scheduleUpdate();

	return true;
}

void Ball::Setup(float x, float y, float gravity)
{
	_rootNode->setPositionX(x);
	_rootNode->setPositionY(y);
	_gravity = gravity;
}

void Ball::update(float deltaTime)
{
	float yPos = _rootNode->getPositionY();
	yPos -= _gravity * deltaTime;
	_rootNode->setPositionY(yPos);
}