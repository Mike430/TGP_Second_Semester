#include "NoGravFieldFX.h"
#include "Game_Scene.h"
#include "ball.h"

bool NoGravFieldFX::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("ZeroGrav.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("sprite");

	return true;
}

void NoGravFieldFX::Hit(Game_Scene* game)
{

	BallManager* balls = game->GetBallMngr();


	for (int i = 0; i < balls->GetNumberOfBalls(); i++)
	{
		balls->GetBallAtIndex(i)->ZeroGravityField = true;
	}

}

int NoGravFieldFX::GetScoreValue() const
{
	return 20;
}