#include "Tutorial_Scene.h"

// Initialisers
//==============================================================================
cocos2d::Scene* Tutorial_Scene::createScene()
{
	auto scene = Game_Scene::createScene();
	auto tutorial = Tutorial_Scene::create();
	tutorial->_game = scene->getChildByName<Game_Scene*>("Game_Scene");
	scene->addChild(tutorial);
	return scene;
}

bool Tutorial_Scene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_rootNode = cocos2d::CSLoader::createNode("TutorialOverlay.csb");
	addChild(_rootNode);

	_text = _rootNode->getChildByName<Text*>("tutorial_text");
	_text->setVisible(false);

	_wasPaused = false;

	this->scheduleUpdate();

	//order based on time, see GameProgression::_events
	_tutorialMessages = {
		"Rocket Ball",
		"Rare Target",
		"Oil Ball",
		"Double Attack Target",
		"Bomb Ball",
		"Invincibility Target",
		"Bomb Other Ball",
		"Zero Gravity Target",
		"Wallet Ball",
		"Double Gravity Target",
		"Powder Ball",
		"Half Gravity Target"
	};
	return true;
}

void Tutorial_Scene::update(float deltaTime)
{
	int events = _game->_gameProgression->GetRemainingEvents();
	if (_prevEventsCount == -1)
	{
		_prevEventsCount = events;
	}
	for (int i = 0; i < _prevEventsCount - events; i++)
	{
		if (!_tutorialMessages.empty())
		{
			Display(_tutorialMessages.front());
			_tutorialMessages.erase(_tutorialMessages.begin());
			_prevEventsCount = _game->_gameProgression->GetRemainingEvents();
		}
	}
	_prevEventsCount = events;
	if (_wasPaused && !_game->IsPaused())
	{
		OnResumeGame();
	}
	_wasPaused = _game->IsPaused();
}

void Tutorial_Scene::Display(string message)
{
	_game->Pause();
	_text->setText(message);
	_text->setVisible(true);
}

void Tutorial_Scene::OnResumeGame()
{
	_text->setVisible(false);
}
