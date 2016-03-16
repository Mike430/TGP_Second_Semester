#pragma once
#ifndef __BALL_H__
#define __BALL_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Settings.h"
using namespace cocos2d;

class Ball : public Node
{
private:
	//Variables for ball dispencer
	int _wayPointIndex;
	Vec2 _dispencerPosition;// position
	bool _advancing;// stops tampering when advancing to next way point.
	bool _contained;// if true, no gravity

	//Variables for gameplay
	bool _collidable;
protected:
	bool _onRight;
	Vec2 _velocity;
	float _gravity;
	float _terminalVel;

	Node* _rootNode;
	//Sprite* _sprite;
public:
	virtual bool init();
	static Ball* create();
	virtual void Setup(Vec2 startPoint, Vec2 next, bool onRight);
	virtual ~Ball();

	// Dispencer Methods
	int GetWayPointIndex() const { return _wayPointIndex; }
	void MoveToNext(Vec2 next, int wayPointIndex);
	void Drop();

	// Game Methods
	float GravityEffect(float position, float deltaTime);
	virtual void Hit(Vec2 velocity);
	bool IsOnRight() const { return _onRight; }


	//general
	bool IsContained() const { return _contained; }
	bool IsCollidable() const { return _collidable; }
	void SetCollidable(bool state) { _collidable = state; }
	
	void SetGravity(float newGrav){ _gravity = newGrav; }

	//bools used to add field effects
	bool ZeroGravityField = false;
	bool HalfGravityField = false;
	bool DoubleGravityField = false;

	virtual void update(float deltaTime);
	virtual void InGameUpdate(float deltaTime);
	virtual void InDispencerUpdate(float deltaTime);
};
#endif // __BALL_H__