#include "Ball.h"

Ball* Ball::create()
{
	Ball* newBall = new Ball();
	newBall->init();
	return newBall;
}

Ball::~Ball()
{

}

bool Ball::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("Ball.csb");
	this->addChild(_rootNode);
	//_sprite = (cocos2d::Sprite*)this->getChildByName("Sprite_1");
	this->scheduleUpdate();

	return true;
}

void Ball::Setup(Vec2 startPoint, Vec2 next, bool onRight)
{
	setPosition(startPoint);

	// Dispencer Variables
	_wayPointIndex = 0;
	_dispencerPosition = next;
	_advancing = false;
	_contained = true;
	_collidable = true;
	_onRight = onRight;

	// Gameplay Variables
	_velocity = Vec2(0, 0);
	_terminalVel = -3000.0f;
	_gravity = 15 * 60;//was 15 per frame at ~60fps, now framerate independant
}

// Gameplay Methods
float Ball::GravityEffect(float position, float deltaTime)
{
	_velocity.y -= _gravity * deltaTime;
	if (_velocity.y < _terminalVel)
	{
		_velocity.y = _terminalVel;
	}
	float newYVector = _velocity.y * deltaTime;//adjust to framerate

	return position + newYVector;
}

void Ball::Hit(Vec2 velocity)
{
	if (_contained) return;
	_velocity = velocity;
	if (_onRight)
	{
		_velocity.x *= -1;
	}
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
	_velocity = Vec2(0, 0);
}

void Ball::update(float deltaTime)
{
	if (!_contained)// not in dispencer then gameplay logic
	{
		InGameUpdate(deltaTime);
	}
	else
	{
		InDispencerUpdate(deltaTime);
	}
}

void Ball::InGameUpdate(float deltaTime)
{
	float yPos = getPositionY();
	yPos = GravityEffect(yPos, deltaTime);
	setPositionY(yPos);

	float xPos = getPositionX();
	xPos += _velocity.x * deltaTime;
	setPositionX(xPos);
}

void Ball::InDispencerUpdate(float deltaTime)
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
