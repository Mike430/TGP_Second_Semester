#pragma once

#include "cocos2d.h"
#include "Game_Scene.h"
#include <functional>
#include <sstream>
using namespace cocos2d;

class Tutorial_Scene : public Layer
{
private:
	Game_Scene* _game;
	Node* _rootNode;
	bool _wasPaused;
	Text* _text;
	//for each message, when the function returns true, display the message
	list<tuple<function<bool()>, function<string()>>> _tutorialMessages;
	bool _zeroGrav, _halfGrav, _doubleGrav;
public:
	CREATE_FUNC(Tutorial_Scene);
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float deltaTime) override;
	void Display(string message);
	void OnResumeGame();
};

