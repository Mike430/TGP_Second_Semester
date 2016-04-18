#pragma once

#include "cocos2d.h"
#include "Game_Scene.h"
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;
using namespace cocos2d;

struct TutorialMessage
{
	string message;
	string spriteFile;
	explicit TutorialMessage(string message)
		: TutorialMessage(message, "") {}
	TutorialMessage(string message, string spriteFile)
		: message(message), spriteFile(spriteFile)  {}
};

class Tutorial_Scene : public Layer
{
private:
	Game_Scene* _game;
	Node* _rootNode;
	bool _wasPaused;
	Text* _text;
	Sprite* _messageSprite;
	Sprite* _messageBackground;
	Button* _resumeButton;
	list<TutorialMessage> _introMessages;
	unordered_map<int, TutorialMessage> _newBallMessages;
	unordered_map<int, TutorialMessage> _newTargetMessages;
	unordered_map<int, TutorialMessage> _winLoseMessages;
	void Display(TutorialMessage message);
	void OnResumeGame();
	void SetOverlayVisible(bool visible);
	void UnPauseGame();

public:
	CREATE_FUNC(Tutorial_Scene);
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float deltaTime) override;
};

