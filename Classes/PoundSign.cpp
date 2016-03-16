#include "PoundSign.h"


PoundSign* PoundSign::create()
{
	PoundSign* boom = new PoundSign();
	boom->init();

	return boom;
}
bool PoundSign::init()
{
	if (!Node::init())
	{
		return false;
	}


	this->_rootNode = cocos2d::CSLoader::createNode("PoundSign.csb");
	this->addChild(_rootNode);

	//_location = currentLocation;
	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("Sprite_1");
	_sprite->setOpacity(255);
	this->scheduleUpdate();

	return true;
}


PoundSign::~PoundSign()
{
}

void PoundSign::update(float deltaTime)
{
	if (_sprite->getOpacity()>10)
	{
		_sprite->setOpacity(_sprite->getOpacity() - 10);
	}
	else
	{
		this->getParent()->removeChild(this);
	}

}