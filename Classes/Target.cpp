#include "Target.h"
#include "Game_Scene.h"

bool Target::init()
{
	if (!Node::init())
	{
		return false;
	}

	//this->_rootNode = cocos2d::CSLoader::createNode("Target.csb");
	//this->addChild(_rootNode);

	//_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("sprite");
	this->setPositionX(rand() % _maxX + _minX);
	this->setPositionY(rand() % _maxY + _minY);

	_lifeTime = Settings::targetLifeTime;

	this->scheduleUpdate();

	return true;
}

//Public Methods
//==============================================================================
void Target::update(float deltaTime)
{
	_lifeTime -= deltaTime;
}

Rect Target::GetCollision() const
{
	return _sprite->getBoundingBox();
}

bool Target::IsLifeTimeOver()
{
	return _lifeTime <= 0;
}