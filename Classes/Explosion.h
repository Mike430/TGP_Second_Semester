#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
class Explosion : public Node
{
private:
	Vec2 _location;
	int _fadeTime;
	cocos2d::Sprite*        _sprite;

protected:
	Node* _rootNode;
public:
	static Explosion* create();
	virtual bool init();
	~Explosion();
	void update(float deltaTime);
};

