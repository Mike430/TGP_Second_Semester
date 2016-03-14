#pragma once
#ifndef _TARGET_H_
#define _TARGET_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
class Game_Scene;

using namespace std;
using namespace cocos2d;

class Target : public Node
{
protected:
	// Positioning
	const int _minX = 300.0f;
	const int _maxX = 650.0f;// <-look into this, apparently the screen is only 1000 wide but we KNOW it's 1280
	const int _minY = 100.0f;
	const int _maxY = 500.0f;

	Node* _rootNode;
	Sprite* _sprite;

	float _lifeTime;
public:
	Target() {};
	virtual ~Target() {};
	virtual bool init();

	virtual void update(float deltaTime);
	virtual void Hit(Game_Scene* game) = 0;
	virtual int GetScoreValue() const = 0;
	virtual Rect GetCollision() const;
	bool IsLifeTimeOver();
};
#endif
