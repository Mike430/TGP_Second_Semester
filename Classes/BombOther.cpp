#include "BombOther.h"

BombOther* BombOther::create()
{
	BombOther* ball = new BombOther();
	ball->init();
	return ball;
}

BombOther::~BombOther()
{

}

bool BombOther::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("BombOther.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->_type = 8;
	this->scheduleUpdate();

	return true;
}


