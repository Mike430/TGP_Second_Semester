#include "NoGravFieldFX.h"
#include "Game_Scene.h"
#include "ball.h"
#include "AudioHelper.h"

bool NoGravFieldFX::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("ZeroGravField.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("sprite");

	return true;
}

void NoGravFieldFX::Hit(Game_Scene* game, Ball* ball)
{

	BallManager* balls = game->GetBallMngr();


	for (int i = 0; i < balls->GetNumberOfBalls(); i++)
	{
		balls->GetBallAtIndex(i)->ZeroGravityField = true;
		balls->GetBallAtIndex(i)->HalfGravityField = false;
		balls->GetBallAtIndex(i)->DoubleGravityField = false;
	}

	//AudioHelper::Play("gravity5");
}

int NoGravFieldFX::GetScoreValue() const
{
	return 20;
}