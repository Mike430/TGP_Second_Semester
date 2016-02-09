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
#include "GameManager.h"
#include "Player.h"
#include "Ball.h"
#include "BallDispencer.h"
#include "BallManager.h"
#include "Target.h"

using namespace std;
using namespace cocos2d;

//=========================================//
class Game_Scene : public cocos2d::Layer
{
private:
	static const int _numbOfTargets = 5;
	cocos2d::Node* _rootNode;
	//Cocos2d UI
	//Button* _endButton;
	Text* _scoreLabel;

	Vec2 _windowSize;

	vector<Player*> _players;
	Player* _leftPlayer;
	Player* _rightPlayer;

	vector<BallDispencer*> _ballDispencers;
	BallDispencer* _leftDispencer;
	BallDispencer* _rightDispencer;
	Target* _targets[_numbOfTargets];

	BallManager* _ballManager;
	float _countDown;
	bool _paused;

	bool TestCollisionWithPlayer(Ball* ball, int ballIndex);
	bool TestCollisionWithTargets(Ball* ball, int ballIndex, int targetIndex);
	bool TestIfBallIsOut(Ball* ball, int ballIndex);
	void SeeSaw(Player* winningPlayer, Player* loosingPlayer, bool amount);
	void EndGame(int player1Score, int player2Score);
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

	void Hit();

	// Callbacks
	//==============================================================================
	//void EndButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouhCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
};
#endif // __GAME_H__
