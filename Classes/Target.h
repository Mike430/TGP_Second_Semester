#pragma once
#ifndef _TARGET_H_
#define _TARGET_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Settings.h"

using namespace std;
using namespace cocos2d;

class Target : public Node
{
private:
	// Positioning
	const int _minX = 300.0f;
	const int _maxX = 650.0f;// <-look into this, apparently the screen is only 1000 wide but we KNOW it's 1280
	const int _minY = 100.0f;
	const int _maxY = 500.0f;

	// Timing (Time in miliseconds)
	const int _maxTimeVisible = Settings::targetMaxTimeVisible;
	const int _minTimeVisible = Settings::targetMinTimeVisible;
	const int _maxTimeInvisible = Settings::targetMaxTimeInvisible;
	const int _minTimeInvisible = Settings::targetMinTimeInvisible;
	const int _range = 20, _rareProb = 18;
	bool _active;
	bool _commonOrRare;

	float _timeTilChange;
	float _currentTime;

	Node* _rootNode;
	Sprite* _commonSPR;
	Sprite* _rareSPR;

	void SetNextTimePeriod(bool visibleOrNot);
	void SetNextState();
	void SetNextPosition();
	void ResetTarget();
public:
	//static Target* create();
	CREATE_FUNC(Target);
	virtual bool init();

	virtual void update(float deltaTime);
	void Hit();

	bool GetActive() const { return _active; }
	bool GetScarcity() const { return _commonOrRare; }
	Rect GetCollision() const { return _commonSPR->getBoundingBox(); }
};
#endif
