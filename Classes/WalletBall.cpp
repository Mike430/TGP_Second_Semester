#include "WalletBall.h"
#include "Game_Scene.h"

WalletBall* WalletBall::create()
{
	WalletBall* ball = new WalletBall();
	ball->init();
	return ball;
}

WalletBall::~WalletBall()
{

}

bool WalletBall::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("Wallet.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->scheduleUpdate();

	return true;
}

void WalletBall::Hit(Vec2 velocity)
{
	PoundSign* boomImage;

	boomImage = PoundSign::create();

	this->getParent()->addChild(boomImage);

	boomImage->setPosition(this->getParent()->convertToWorldSpace(this->getPosition()));

	((Game_Scene*)(this->getParent()->getParent()))->DestroyAndDropBall(this);

}
