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

	_zeroGrav = _halfGrav = _doubleGrav = false;

	_tutorialMessages.push_back(make_tuple(
		[]() { return true; }, 
		[]() { return "Tap unpause to start the game\nWhile playing, tap the screen to swing your bat"; })
	);
	_tutorialMessages.push_back(make_tuple(
		[this]() { return _zeroGrav; },
		[this]()
		{
			stringstream message;
			message << "Zero gravity has been enabled for ";
			message << Settings::ZeroGravityFieldDuration;
			message << " seconds.";
			return message.str();
		})
	);
	_tutorialMessages.push_back(make_tuple(
		[this]() { return _halfGrav; },
		[this]()
		{
			stringstream message;
			message << "Half gravity has been enabled for ";
			message << Settings::HalfGravityFieldDuration;
			message << " seconds.";
			return message.str();
		})
	);
	_tutorialMessages.push_back(make_tuple(
		[this]() { return _doubleGrav; },
		[this]()
		{
			stringstream message;
			message << "Double gravity has been enabled for ";
			message << Settings::DoubleGravityFieldDuration;
			message << " seconds.";
			return message.str();
		})
	);
	return true;
}

void Tutorial_Scene::update(float deltaTime)
{
	for (int i = 0; i < _game->_ballManager->GetNumberOfBalls(); i++)
	{
		Ball* ball = _game->_ballManager->GetBallAtIndex(i);
		if (ball->ZeroGravityField) _zeroGrav = true; break;
		if (ball->DoubleGravityField) _doubleGrav = true; break;
		if (ball->HalfGravityField) _halfGrav = true; break;
	}
	for (auto it = _tutorialMessages.begin(); it != _tutorialMessages.end(); it++)
	{
		function<bool()>& trigger = get<0>(*it);
		function<string()>& message = get<1>(*it);
		if (trigger())
		{
			Display(message());
			_tutorialMessages.erase(it);
			break;
		}
	}
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
