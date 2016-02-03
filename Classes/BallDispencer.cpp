#include "BallDispencer.h"

BallDispencer* BallDispencer::create()
{
	BallDispencer* newBallBank = new BallDispencer();
	newBallBank->init();
	return newBallBank;
}

bool BallDispencer::init()
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = cocos2d::CSLoader::createNode("BallDispenced.csb");
	this->addChild(_rootNode);
	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("Sprite_1");

	return true;
}

void BallDispencer::Setup(bool leftOrRight, float x, float y)
{
	if (leftOrRight){
		float size = _sprite->getScaleX();
		size *= -1;
		_sprite->setScaleX(size);
	}

	_sprite->setPositionX(x);
	_sprite->setPositionY(y);
}
