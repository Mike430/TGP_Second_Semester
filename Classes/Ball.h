#pragma once
#ifndef __BALL_H__
#define __BALL_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
class Ball : public cocos2d::Node
{
private:
	float _gravity;
	cocos2d::Node* _rootNode;
	cocos2d::Sprite* _sprite;
public:
	virtual bool init();
	static Ball* create();
	void Setup(float x, float y, float gravity);

	void update(float deltaTime);
};
#endif // __BALL_H__