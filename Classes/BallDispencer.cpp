#include "BallDispencer.h"

BallDispencer* BallDispencer::create()
{
	BallDispencer* newBallBank = new BallDispencer();
	newBallBank->init();
	return newBallBank;
}

bool BallDispencer::init()
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = cocos2d::CSLoader::createNode("BallDispencer.csb");
	this->addChild(_rootNode);
	_sprite = (cocos2d::Sprite*)_rootNode->getChildByName("Sprite_1");

	for (int i = 0; i < 15; i++)// load all of the way points
	{
		int number = i + 1;
		string newString = "Node_" + to_string(number);
		_nodes[i] = (cocos2d::Node*)_rootNode->getChildByName(newString);
		//this->addChild(_nodes[i]);
	}

	return true;
}

void BallDispencer::Setup(bool leftOrRight, float x, float y, BallManager* manager)
{
	if (leftOrRight){
		float size = _sprite->getScaleX();
		size *= -1;
		_sprite->setScaleX(size);

		for (int i = 0; i < 15; i++)
		{
			float pos = _nodes[i]->getPositionX();
			pos *= -1;
			_nodes[i]->setPositionX(pos);
		}
	}

	_sprite->setPositionX(x);
	_sprite->setPositionY(y);

	_ballManager = manager;
}

void BallDispencer::AddBall()
{
	Ball* tempBall = _ballManager->CreateBall(_rootNode);
	tempBall->Setup(_nodes[0]->getPosition(), 10.0f, _nodes[14 - _containedBalls.size()]->getPosition());
	_containedBalls.push_back(tempBall);
}

void BallDispencer::DropBall()
{
	Ball* toDrop = _containedBalls.front();
	//remove as child, set as child of parent(scene)
	_rootNode->removeChild(toDrop);
	getParent()->addChild(toDrop);
	toDrop->Drop();
	_containedBalls.erase(_containedBalls.begin());
	//move up next balls
	for (int i = 0; i < _containedBalls.size(); i++)
	{
		_containedBalls[i]->MoveToNext(_nodes[14 - i]->getPosition(), 14 - i);
	}
}

void BallDispencer::update(float deltaTime)
{
	_spawnTimer += deltaTime;
	if (_spawnTimer >= 2)
	{
		_spawnTimer = 0;
		DropBall();
	}
}