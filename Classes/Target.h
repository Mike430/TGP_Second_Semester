#pragma once
#ifndef _TARGET_H_
#define _TARGET_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;

class Target : public Node
{
private:
	// Positioning
	const int _minX = 400.0f;
	const int _maxX = 500.0f;
	const int _minY = 100.0f;
	const int _maxY = 200.0f;

	// Timing (Time in miliseconds)
	const int _maxTimeVisible = 4000;
	const int _minTimeVisible = 3000;
	const int _maxTimeInvisible = 3000;
	const int _minTimeInvisible = 500;
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
	static Target* create();
	bool init();

	void update(float deltaTime);
	void Hit();

	bool GetActive() const { return _active; }
	bool GetScarcity() const { return _commonOrRare; }
	Rect GetCollision() const { return _commonSPR->getBoundingBox(); }
};
#endif
