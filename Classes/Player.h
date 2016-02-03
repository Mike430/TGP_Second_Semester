#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Ball.h"
#include "BallManager.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Player : public Node
{
private:
	cocos2d::Node* _rootNode;
	Button* _swingButton;
	BallManager* _ballManager;
	void SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
public:
	virtual bool init(const string csbFile, BallManager* ballManager);
	static Player* create(const string csbFile, BallManager* ballManager);
	void update(float delta);
};

