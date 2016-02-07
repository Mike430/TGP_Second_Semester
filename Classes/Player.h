#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Ball.h"
#include "BallManager.h"
#include "BallDispencer.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Player : public Node
{
private:
	Node* _rootNode;
	Button* _swingButton;
	BallManager* _ballManager;
	BallDispencer* _ballDispencer;

	int _score;

	void SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
public:
	virtual bool init(const string csbFile, BallManager* ballManager, BallDispencer* ballDispencer);
	static Player* create(const string csbFile, BallManager* ballManager, BallDispencer* ballDispencer);
	void update(float delta);
	void addScore(int points);
	int getScore();
};

