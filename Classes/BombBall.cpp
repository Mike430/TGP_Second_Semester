#include "BombBall.h"
#include "Game_Scene.h"

BombBall* BombBall::create()
{
	BombBall* ball = new BombBall();
	ball->init();
	return ball;
}

BombBall::~BombBall()
{

}

bool BombBall::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->_type = 9;
	this->_rootNode = cocos2d::CSLoader::createNode("Bomb.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");
	this->scheduleUpdate();

	return true;
}

void BombBall::Hit(Vec2 velocity)
{
	
	/*if (Settings::dropRate == -1)
	{
		(this->IsOnRight() ? _rightDispencer : _leftDispencer)->DropBall();
	}
	_ballManager->DestroyBall(ball);*/
	Explosion* boomImage;
	boomImage = Explosion::create();
	this->getParent()->addChild(boomImage);
	boomImage->setPosition(this->getParent()->convertToWorldSpace(this->getPosition()));
	boomImage->setZOrder(this->getZOrder());
	((Game_Scene*)(this->getParent()->getParent()))->DestroyAndDropBall(this);
}

