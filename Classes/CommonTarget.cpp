#include "CommonTarget.h"
#include "Game_Scene.h"

bool CommonTarget::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("CommonTarget.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("sprite");

	return true;
}

void CommonTarget::Hit(Game_Scene* game)
{

}

int CommonTarget::GetScoreValue() const
{
	return 5;
}