#include "Target.h"

// Initialisers
//==============================================================================
//Target* Target::create()
//{
//	Target* newTarget = new Target();
//	newTarget->init();
//	return newTarget;
//}

bool Target::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->_rootNode = cocos2d::CSLoader::createNode("Target.csb");
	this->addChild(_rootNode);

	_commonSPR = (cocos2d::Sprite*)_rootNode->getChildByName("common_Sprite");
	_rareSPR = (cocos2d::Sprite*)_rootNode->getChildByName("rare_Sprite");
	ResetTarget();
	_currentTime = 0.0f;
	_active = false;

	this->scheduleUpdate();

	return true;
}

// Private Methods
//==============================================================================
void Target::SetNextTimePeriod(bool visibleOrNot)
{
	int randTime;
	if (visibleOrNot)
		randTime = rand() % _maxTimeVisible + _minTimeVisible;
	else
		randTime = rand() % _maxTimeInvisible + _minTimeInvisible;

	float visibleTime = (float)randTime / 1000;
	_timeTilChange = visibleTime;
}

void Target::SetNextState()
{
	int determiner;
	determiner = rand() % _range + 0;

	if (determiner >= _rareProb)
		_commonOrRare = true;
	else
		_commonOrRare = false;
}

void Target::SetNextPosition()
{
	Vec2 nextPos;
	nextPos.x = rand() % _maxX + _minX;
	nextPos.y = rand() % _maxY + _minY;
	this->setPosition(nextPos);
}

void Target::ResetTarget()
{
	_active = false;
	_rareSPR->setVisible(false);
	_commonSPR->setVisible(false);

	SetNextTimePeriod(false);// time invisible
	SetNextState();// what you will be when you reappear
	SetNextPosition();// where you will be when you reappear
}

//Public Methods
//==============================================================================
void Target::update(float deltaTime)
{
	if (_currentTime >= _timeTilChange)
	{
		_currentTime = 0.0f;
		if (_active)
		{
			ResetTarget();
		}
		else
		{
			_active = true;
			SetNextTimePeriod(true);// Duration for being active

			if (_commonOrRare)
				_rareSPR->setVisible(true);
			else
				_commonSPR->setVisible(true);
		}
	}
	else
		_currentTime += deltaTime;
}

void Target::Hit()
{
	ResetTarget();
}
