#pragma once

#include "cocos2d.h"
#include "Game_Scene.h"
using namespace cocos2d;

class Tutorial_Scene : public Layer
{
private:
	Game_Scene* _game;
	Node* _rootNode;
	bool _wasPaused;
	Text* _text;
public:
	CREATE_FUNC(Tutorial_Scene);
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float deltaTime) override;
	void OnResumeGame();
	float asdf = 0;
};

