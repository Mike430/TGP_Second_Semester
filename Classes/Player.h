#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace std;

class Player : public Node
{
public:
	Player(const string csbFile, const Vec2 position);
	~Player();

	virtual bool init() override;
	static Player* create(const string csbFile, const Vec2 position);
	void update(float delta);
};

