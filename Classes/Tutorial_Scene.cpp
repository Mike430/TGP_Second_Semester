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

	return true;
}

void Tutorial_Scene::update(float deltaTime)
{
	if (_wasPaused && !_game->IsPaused())
	{
		OnResumeGame();
	}
	_wasPaused = _game->IsPaused();
	asdf += deltaTime;
	if (asdf > 3)
	{
		asdf = -100;
		_game->Pause();
		_text->setText("Tap the screen to swing your bat!");
		_text->setVisible(true);
	}
}

void Tutorial_Scene::OnResumeGame()
{
	_text->setVisible(false);
}
