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

void Ball::Setup(Vec2 startPoint, float gravity, Vec2 next, bool leftOrRight)
{
	setPosition(startPoint);

	// Dispencer Variables
	_wayPointIndex = 0;
	_dispencerPosition = next;
	_advancing = false;
	_contained = true;
	_leftOrRight = leftOrRight;

	// Gameplay Variables
	_inflect = 20.0f;
	_yVector = 0.0f;
	_xVector = 0.0f;
	_terminalVel = -3000.0f;
	_gravity = gravity;
}

// Gameplay Methods
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

void Ball::Hit(Vec2 velocity)
{
	if (_contained) return;
	_xVector = 500.0f * (velocity.x > 0 ? 1 : -1);
	_yVector = 350.0f;
}

// Dispencer methods
void Ball::MoveToNext(Vec2 next, int wayPointIndex)
{
	_advancing = false;
	_dispencerPosition = next;
	_wayPointIndex = wayPointIndex;
}

void Ball::Drop()
{
	_contained = false;
	_yVector = 0.0f;
	_xVector = 0.0f;
}

void Ball::update(float deltaTime)
{
	if (!_contained)// not in dispencer then gameplay logic
	{
		float yPos = getPositionY();
		yPos = GravityEffect(yPos, deltaTime);
		setPositionY(yPos);

		float xPos = getPositionX();
		xPos += _xVector * deltaTime;
		setPositionX(xPos);
	}
	else
	{
		if (this->getPosition() != _dispencerPosition && !_advancing)
		{
			_advancing = true;
			MoveTo* moveVec = MoveTo::create(0.25f, _dispencerPosition);
			this->runAction(moveVec);
		}
		if (this->getPosition() == _dispencerPosition)
		{
			_advancing = false;
		}
	}
}

