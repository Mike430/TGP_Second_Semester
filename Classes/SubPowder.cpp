#include "SubPowder.h"

SubPowder* SubPowder::create()
{
	SubPowder* ball = new SubPowder();
	ball->init();
	return ball;
}

SubPowder::~SubPowder()
{

}

bool SubPowder::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("PowderSub.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");

	this->scheduleUpdate();
	//_contained = false;

	return true;
}

void SubPowder::Hit(Vec2 velocity)
{
//	if (_contained) return;
	_velocity = velocity;
	
	//if 0 gravity field is active set gravity to 0
	if (ZeroGravityField)
	{
		_gravity = 0;
	}
	else if (HalfGravityField)
	{
		_gravity = Settings::gravity * Settings::HalfGravityStrength;
	}

	else if (DoubleGravityField)
	{
		_gravity = Settings::gravity * Settings::DoubleGravityStrength;
	}

	else 
	{
		_gravity = Settings::gravity;
	}

}


void SubPowder::update(float deltaTime)
{
	float yPos = getPositionY();
	yPos = GravityEffect(yPos, deltaTime);
	setPositionY(yPos);

	float xPos = getPositionX();
	xPos += _velocity.x * deltaTime;
	setPositionX(xPos);


}

