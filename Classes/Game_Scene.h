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
#include "AudioHelper.h"
#include "GameManager.h"
#include "Player.h"
#include "BallDispencer.h"
#include "BallManager.h"
#include "TargetManager.h"
#include "GameProgression.h"
#include "AnimationHelper.h"

using namespace std;
using namespace cocos2d;


//=========================================//
class Game_Scene : public cocos2d::Layer
{
	friend class Tutorial_Scene;
	friend class GameProgression;
private:
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
	vector<Target*> _targets;
	cocos2d::ui::Button* _mainMenu;
	float _targetSpawnTimer;

	BallManager* _ballManager;
	TargetManager* _targetManager;
	GameProgression* _gameProgression;

	float _countDown;

	bool _paused;
	Button* _unPauseButton;

	// timers for diffrent field effect so they can have diffrent duration
	float _NoGravTimer = Settings::ZeroGravityFieldDuration;
	float _HalfGravTimer = Settings::HalfGravityFieldDuration;
	float _DoubleGravTimer = Settings::DoubleGravityFieldDuration;

	bool TestCollisionWithPlayer(Ball* ball);
	bool TestCollisionWithTarget(Ball* ball, Target* target);
	bool TestIfBallIsOut(Ball* ball);
	
	
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
	BallManager* GetBallMngr() { return _ballManager; }

	// Game Methods
	//==============================================================================
	void update(float deltaTime);

	void Hit();

	Player* GetBallHitter(Ball* ball);

	void DestroyAndDropBall(Ball* ball);
	void SeeSaw(Player* player, int amount);

	void PowderBallActivate(Ball* ball);
	// Callbacks
	//==============================================================================
	//void EndButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouhCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void MainMenuButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void Pause();
	void UnPause();
	bool IsPaused();
	void EnableUpdates(bool enable);
};
#endif // __GAME_H__
