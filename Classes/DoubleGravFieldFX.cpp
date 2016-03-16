#include "DoubleGravFieldFX.h"
#include "Game_Scene.h"
#include "ball.h"

bool DoubleGravFieldFX::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("DoubleGravField.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("sprite");

	return true;
}

void DoubleGravFieldFX::Hit(Game_Scene* game)
{

	BallManager* balls = game->GetBallMngr();


	for (int i = 0; i < balls->GetNumberOfBalls(); i++)
	{
		balls->GetBallAtIndex(i)->DoubleGravityField = true;
		balls->GetBallAtIndex(i)->ZeroGravityField = false;
		balls->GetBallAtIndex(i)->HalfGravityField = false;
	}

}

int DoubleGravFieldFX::GetScoreValue() const
{
	return 20;
}