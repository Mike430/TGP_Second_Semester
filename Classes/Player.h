#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Ball.h"
#include "BallManager.h"
#include "BallDispencer.h"
#include "Settings.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Player : public Node
{
private:
	Node* _rootNode;
	Button* _swingButton;
	Sprite* _normalSPR;
	Sprite* _dazedSPR;
	Sprite* _vDazedSPR;

	BallManager* _ballManager;
	BallDispencer* _ballDispencer;

	int _score;
	bool _dazedState;
	bool _veryDazed;

	float _timeOut;

	//void SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	
public:
	virtual bool init(const string csbFile, BallManager* ballManager, BallDispencer* ballDispencer);
	static Player* create(const string csbFile, BallManager* ballManager, BallDispencer* ballDispencer);
	void update(float deltaTime);
	void SwingBat();
	void PlayerHitByBall(Ball* ball);
	void addScore(int points);
	int getScore();
};

