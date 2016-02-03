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

void BallDispencer::Setup(bool leftOrRight, float x, float y)
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
}

void BallDispencer::GetNextWaypoint(cocos2d::Node* position, int* index)
{

}