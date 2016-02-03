#pragma once
#ifndef __BALL_DISPENCER_H__
#define __BALL_DISPENCER_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <string>

using namespace std;

class BallDispencer : public cocos2d::Node
{
private:
	cocos2d::Node* _rootNode;
	cocos2d::Sprite* _sprite;
	cocos2d::Node* _nodes[15];
public:
	static BallDispencer* create();
	bool init();
	void Setup(bool leftOrRight, float x, float y);

	void GetNextWaypoint(cocos2d::Node* position, int* index);
};
#endif // __BALL_DISPENCER_H__
