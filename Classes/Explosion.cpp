#include "Explosion.h"


Explosion* Explosion::create()
{
	Explosion* boom = new Explosion();
	boom->init();
	
	return boom;
}
bool Explosion::init()
{
	if (!Node::init())
	{
		return false;
	}
	

	this->_rootNode = cocos2d::CSLoader::createNode("Explosion.csb");
	this->addChild(_rootNode);
	
	//_location = currentLocation;
	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("Sprite_1");
	_sprite->setOpacity(255);
	this->scheduleUpdate();

	return true;
}


Explosion::~Explosion()
{
}

void Explosion::update(float deltaTime)
{
	if (_sprite->getOpacity()>0)
	{
		_sprite->setOpacity(_sprite->getOpacity() - 3);
	}
	else
	{
		this->getParent()->removeChild(this);
	}

}