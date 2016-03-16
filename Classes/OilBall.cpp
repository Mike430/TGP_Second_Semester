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

	this->_rootNode = cocos2d::CSLoader::createNode("Oil.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->scheduleUpdate();

	return true;
}


