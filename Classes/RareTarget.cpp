#include "RareTarget.h"
#include "Game_Scene.h"
#include "FieldFXManager.h"

bool RareTarget::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("RareTarget.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("sprite");

	return true;
}

void RareTarget::Hit(Game_Scene* game)
{

	BallManager* balls = game->GetBallMngr();


	for (int i = 0; i < balls->GetNumberOfBalls(); i++)
	{
		 balls->GetBallAtIndex(i)->ZeroGravityField = true;
	}
}

int RareTarget::GetScoreValue() const
{
	return 20;
}