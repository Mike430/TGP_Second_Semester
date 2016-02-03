#pragma once
#ifndef __BALL_H__
#define __BALL_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;

class Ball : public Node
{
private:
	float _inflect;
	float _yVector;
	float _xVector;
	float _gravity;
	float _terminalVel;
	Node* _rootNode;
	Sprite* _sprite;
public:
	virtual bool init();
	static Ball* create();
	void Setup(float x, float y, float gravity);

	float GravityEffect(float position, float deltaTime);
	void Hit(Vec2 velocity);

	void update(float deltaTime);
};
#endif // __BALL_H__