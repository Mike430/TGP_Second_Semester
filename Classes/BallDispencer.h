#pragma once
#ifndef __BALL_DISPENCER_H__
#define __BALL_DISPENCER_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
#include "BallManager.h"
#include "Settings.h"

using namespace std;

class BallDispencer : public cocos2d::Node
{
private:
	cocos2d::Node* _rootNode;
	cocos2d::Sprite* _backSprite;
	cocos2d::Sprite* _frontSprite;
	cocos2d::ui::Text* _scoreLabel;
	cocos2d::Node* _nodes[15];

	BallManager* _ballManager;
	vector<Ball*> _containedBalls;
	float _spawnTimer;
public:
	static BallDispencer* create();
	bool init();
	void update(float deltaTime);
	void Setup(bool leftOrRight, float x, float y, BallManager* manager);
	void AddBall();
	void DropBall();
	void DisplayScore(int score);
	void DisplayText(string text);
};
#endif // __BALL_DISPENCER_H__
