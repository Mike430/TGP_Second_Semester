#include "Ball.h"


Ball* Ball::create()
{
	Ball* newBall = new Ball();
	newBall->init();
	return newBall;
}

bool Ball::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("Ball.csb");
	this->addChild(_rootNode);
	_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");
	this->scheduleUpdate();

	return true;
}

void Ball::Setup(float x, float y, float gravity)
{
	setPositionX(x);
	setPositionY(y);
	_inflect = 20.0f;
	_yVector = 500.0f;
	_xVector = (rand() % 10 + 0) * 10;
	_terminalVel = -3000.0f;
	_gravity = 10;
}

//
float Ball::GravityEffect(float position, float deltaTime)
{
	
	if (_yVector > _terminalVel)// if ball is above terminal velocity
	{
		_yVector -= _gravity;
	}
	else
		_yVector = _terminalVel;

	float newYVector = _yVector * deltaTime;//adjust to framerate

	return position += newYVector;
}

//
void Ball::update(float deltaTime)
{
	float yPos = getPositionY();
	yPos = GravityEffect(yPos, deltaTime);
	setPositionY(yPos);

	float xPos = getPositionX();
	xPos += _xVector * deltaTime;
	setPositionX(xPos);
}

void Ball::Hit(Vec2 velocity)
{
	_xVector = 500.0f * (velocity.x > 0 ? 1 : -1);
	_yVector = 350.0f;
}