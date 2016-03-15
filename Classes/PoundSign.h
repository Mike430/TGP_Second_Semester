#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
class PoundSign : public Node
{
private:
	Vec2 _location;
	int _fadeTime;
	cocos2d::Sprite*        _sprite;

protected:
	Node* _rootNode;
public:
	static PoundSign* create();
	virtual bool init();
	~PoundSign();
	void update(float deltaTime);
};

