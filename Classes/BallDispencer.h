#pragma once
#ifndef __BALL_DISPENCER_H__
#define __BALL_DISPENCER_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class BallDispencer : public cocos2d::Node
{
private:
	cocos2d::Node* _rootNode;
	cocos2d::Sprite* _sprite;
public:
	static BallDispencer* create();
	bool init();
	void Setup(bool leftOrRight, float x, float y);
};
#endif // __BALL_DISPENCER_H__
