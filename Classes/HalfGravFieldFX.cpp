#include "HalfGravFieldFX.h"
#include "Game_Scene.h"
#include "ball.h"

bool HalfGravFieldFX::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("HalfGravField.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("sprite");

	return true;
}

void HalfGravFieldFX::Hit(Game_Scene* game, Ball* ball)
{

	BallManager* balls = game->GetBallMngr();


	for (int i = 0; i < balls->GetNumberOfBalls(); i++)
	{
		balls->GetBallAtIndex(i)->HalfGravityField = true;
		balls->GetBallAtIndex(i)->ZeroGravityField = false;
		balls->GetBallAtIndex(i)->DoubleGravityField = false;
	}

}

int HalfGravFieldFX::GetScoreValue() const
{
	return 20;
}