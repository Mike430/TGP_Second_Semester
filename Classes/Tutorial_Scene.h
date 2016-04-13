#pragma once

#include "cocos2d.h"
#include "Game_Scene.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
using namespace cocos2d;

class Tutorial_Scene : public Layer
{
private:
	Game_Scene* _game;
	Node* _rootNode;
	bool _wasPaused;
	Text* _text;
	vector<string> _tutorialMessages;
	int _prevEventsCount = -1;
public:
	CREATE_FUNC(Tutorial_Scene);
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float deltaTime) override;
	void Display(string message);
	void OnResumeGame();
};

