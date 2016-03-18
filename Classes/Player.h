#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Ball.h"
#include "BallManager.h"
#include "BallDispencer.h"
#include "Settings.h"
#include "Explosion.h"
#include "AnimationHelper.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class Player : public Node
{
private:
	Node* _rootNode;
	Button* _swingButton;
	Sprite* _sprite;
	Sprite* _collisionSprite;

	BallManager* _ballManager;
	BallDispencer* _ballDispencer;

	int _score;

	bool _dazedState;
	bool _veryDazed;
	bool IsDazed() { return _dazedState || _veryDazed; }

	// Player PowerUp Settings
	bool _invincible = false;
	bool _doubleAttack = false;
	float _invincibleTime;
	float _doubleAttackTime;

	float _timeSinceHit;
	float _stunLockTimer;

	//void SwingButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	
public:
	virtual bool init(bool onRight, BallManager* ballManager, BallDispencer* ballDispencer);
	static Player* create(bool onRight, BallManager* ballManager, BallDispencer* ballDispencer);
	void update(float deltaTime);
	void SwingBat();

	void SetInvincible();
	void SetDoubleAttack();

	bool IsInvincible();
	Rect GetCollision();

	void PlayerHitByBall(Ball* ball);
	void Daze(bool extendedTime = false);
	void EndDaze();

	void addScore(int points);
	int getScore();
};

