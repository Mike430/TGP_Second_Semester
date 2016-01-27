#pragma once
#ifndef __GAME_H__
#define __GAME_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Score_Scene.h"
#include "ui/CocosGUI.h"
#include <string.h>
#include "SimpleAudioEngine.h"

using namespace std;

//=========================================//
class Game_Scene : public cocos2d::Layer
{
private:
	cocos2d::Node* _rootNode;
	//Cocos2d UI
	cocos2d::ui::Button* _endButton;
	cocos2d::ui::Text* _scoreLabel;
	// Gameplay Elements (replace with GameManager Class)
	float _score;
	bool _increment;
public:
	// Initialisers
	//==============================================================================
	cocos2d::Scene* _nextScene;
	//Implements the "createScene()"
	CREATE_FUNC(Game_Scene);
	//Sets up the scene
	static cocos2d::Scene* createScene();
	//Basically a cocos constructor
	virtual bool init();
	//Custom Methods
	void BeginButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	// Game Methods
	//==============================================================================
	void update(float deltaTime);

	// Callbacks
	//==============================================================================
	void EndButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouhCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
};
#endif // __GAME_H__
