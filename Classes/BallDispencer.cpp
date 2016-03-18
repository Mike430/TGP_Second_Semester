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

	_backSprite = (cocos2d::Sprite*)_rootNode->getChildByName("Sprite_1");
	_frontSprite = (cocos2d::Sprite*)_rootNode->getChildByName("Sprite_2");
	_scoreLabel = (cocos2d::ui::Text*)_rootNode->getChildByName("Score_Label");

	_frontSprite->setZOrder(1);
	_scoreLabel->setZOrder(2);

	for (int i = 0; i < 15; i++)// load all of the way points
	{
		int number = i + 1;
		string newString = "Node_" + StringUtils::format("%d", number);
		_nodes[i] = (cocos2d::Node*)_rootNode->getChildByName(newString);
		//_nodes[i]->setPosition(_rootNode->convertToWorldSpace(_nodes[i]->getPosition()));
		//_rootNode->addChild(_nodes[i]);
	}

	_spawnTimer = 0.0f;
	this->scheduleUpdate();

	return true;
}

void BallDispencer::Setup(bool leftOrRight, float x, float y, BallManager* manager)
{
	if (leftOrRight){
		float size = _backSprite->getScaleX();
		size *= -1;
		_backSprite->setScaleX(size);
		_frontSprite->setScaleX(size);

		float scorePos = _scoreLabel->getPositionX();
		scorePos *= -1;
		_scoreLabel->setPositionX(scorePos);

		for (int i = 0; i < 15; i++)
		{
			float pos = _nodes[i]->getPositionX();
			pos *= -1;
			_nodes[i]->setPositionX(pos);
		}
	}

	this->setPositionX(x);
	this->setPositionY(y);

	_ballManager = manager;
}

void BallDispencer::AddBall()
{
	Ball* tempBall = _ballManager->CreateBall(_rootNode, false);
	tempBall->Setup(_nodes[14 - _containedBalls.size()]->getPosition(), _nodes[14 - _containedBalls.size()]->getPosition(), (this->getPositionX() > 500));
	_containedBalls.push_back(tempBall);
}

void BallDispencer::DropBall()
{
	Ball* toDrop = _containedBalls.front();
	Vec2 posRelativeToDispencer = toDrop->getPosition();
	Vec2 posRelativeToWorld = this->convertToWorldSpace(posRelativeToDispencer);
	toDrop->retain();
	toDrop->removeFromParentAndCleanup(false);
	getParent()->addChild(toDrop);
	toDrop->setPosition(posRelativeToWorld);
	toDrop->release();
	toDrop->Drop();
	toDrop->setZOrder(0);
	_containedBalls.erase(_containedBalls.begin());
	//move up next balls
	for (int i = 0; i < _containedBalls.size(); i++)
	{
		_containedBalls[i]->MoveToNext(_nodes[14 - i]->getPosition(), 14 - i);
	}
	//top up
	AddBall();
}

void BallDispencer::update(float deltaTime)
{
	if (Settings::dropRate != -1)
	{
		_spawnTimer += deltaTime;
		if (_spawnTimer >= (1.0f / Settings::dropRate))
		{
			_spawnTimer = 0;
			DropBall();
		}
	}
}

void BallDispencer::DisplayScore(int score)
{
	//_scoreLabel->setText( to_string(score));
	_scoreLabel->setText(StringUtils::format("%d", score));
}