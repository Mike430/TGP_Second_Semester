#include "Player.h"

Player::Player(const string csbFile, const Vec2 position)
{
	Node* player = CSLoader::createNode(csbFile);
	//sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	addChild(player);
	setPosition(position);
}

Player::~Player()
{
}

Player* Player::create(const string csbFile, const Vec2 position)
{
	Player* player = new Player(csbFile, position);
	if (!player->init())
	{
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	player->autorelease();

	return player;
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->scheduleUpdate();

	return true;
}

void Player::update(float delta)
{
	
}