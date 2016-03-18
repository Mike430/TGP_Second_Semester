#include "Invincibility.h"
#include "Game_Scene.h"


Invincibility::Invincibility()
{
}


Invincibility::~Invincibility()
{
}

bool Invincibility::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("Invincibility.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("Invincibility");

	return true;
}

void Invincibility::Hit(Game_Scene* game, Ball* ball)
{
	// Returns the player who hit the ball
	Player* hitter = game->GetBallHitter(ball);
	hitter->SetInvincible();
}

int Invincibility::GetScoreValue() const
{
	return 20;
}