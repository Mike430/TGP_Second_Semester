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
	_rootNode->setPositionX(x);
	_rootNode->setPositionY(y);
	_inflect = 20.0f;
	_yVector = 500.0f;
	_xVector = (rand() % 10 + 0) * 10;
	_terminalVel = -3000.0f;
}

//
float Ball::GravityEffect(float position, float deltaTime)
{
	
	if (_yVector > _terminalVel)// if ball is above terminal velocity
	{
		if (_yVector > _inflect)// if going up
			_yVector = _yVector * 0.95;// decelerate

		if (_yVector < -_inflect)// if going down
			_yVector = _yVector * 1.05;// accelerate

		if (_yVector <= _inflect && _yVector >= -_inflect)// if going very slow
			_yVector = -_inflect + -0.5;// get on with it
	}
	else
		_yVector = _terminalVel;

	float newYVector = _yVector * deltaTime;//adjust to framerate

	return position += newYVector;
}

//
void Ball::update(float deltaTime)
{
	float yPos = _rootNode->getPositionY();
	yPos = GravityEffect(yPos, deltaTime);
	_rootNode->setPositionY(yPos);

	float xPos = _rootNode->getPositionX();
	xPos += _xVector * deltaTime;
	_rootNode->setPositionX(xPos);
}