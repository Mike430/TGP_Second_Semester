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
	bool _leftOrRight;
	float _inflect;
	float _yVector;
	float _xVector;
	float _gravity;
	float _terminalVel;

	Node* _rootNode;
	Sprite* _sprite;

	//Variables for ball dispencer
	int _wayPointIndex;
	Vec2 _dispencerPosition;// position
	bool _advancing;// stops tampering when advancing to next way point.
	bool _contained;// if true, no gravity

	//Variables for gameplay
	bool _collidable;
public:
	virtual bool init();
	static Ball* create();
	void Setup(Vec2 startPoint, float gravity, Vec2 next, bool leftOrRight);

	// Dispencer Methods
	int GetWayPointIndex() const { return _wayPointIndex; }
	void MoveToNext(Vec2 next, int wayPointIndex);
	void Drop();

	// Game Methods
	float GravityEffect(float position, float deltaTime);
	void Hit(Vec2 velocity);
	bool GetLeftOrRight() const { return _leftOrRight; }

	//general
	bool IsContained() const { return _contained; }
	bool IsCollidable() const { return _collidable; }
	void SetCollidable(bool state) { _collidable = state; }

	void update(float deltaTime);
};
#endif // __BALL_H__