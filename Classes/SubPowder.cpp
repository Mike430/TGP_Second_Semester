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

	this->_rootNode = cocos2d::CSLoader::createNode("PowderSub.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->scheduleUpdate();
	//_contained = false;

	return true;
}

void SubPowder::Setup(Vec2 position, bool onRight)
{
	Ball::Setup(position, Vec2(), true);
	_contained = false;
	_onRight = onRight;
}
