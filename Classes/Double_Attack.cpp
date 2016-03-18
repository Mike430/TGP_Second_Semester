#include "Double_Attack.h"
#include "Game_Scene.h"


Double_Attack::Double_Attack()
{
}


Double_Attack::~Double_Attack()
{
}

bool Double_Attack::init()
{
	if (!Target::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("DoubleAttack.csb");
	this->addChild(_rootNode);

	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("DoubleAttack");

	return true;
}

void Double_Attack::Hit(Game_Scene* game, Ball* ball)
{
	Player* hitter = game->GetBallHitter(ball);
	hitter->SetDoubleAttack();
}

int Double_Attack::GetScoreValue() const
{
	return 20;
}
