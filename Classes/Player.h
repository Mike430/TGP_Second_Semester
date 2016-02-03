#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Ball.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Player : public Node
{
private:
	cocos2d::Node* _rootNode;
	Button* _swingButton;
	void SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
public:
	virtual bool init(const string csbFile, const Vec2 position);
	static Player* create(const string csbFile, const Vec2 position);
	void update(float delta);
};

