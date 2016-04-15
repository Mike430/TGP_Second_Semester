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

	_newBallMessages = unordered_map<int, string>{
		{ RocketBall().getType(), "Rocket Ball"},
		{ OilBall().getType(), "Oil Ball" },
		{ BombBall().getType(), "Bomb Ball" },
		{ BombOther().getType(), "Bomb Other Ball" },
		{ WalletBall().getType(), "Wallet Ball" },
		{ PowderBall().getType(), "Powder Ball" }
	};
	_newTargetMessages = unordered_map<int, string>{
		{ RareTarget().getType(), "Rare Target" },
		{ Double_Attack().getType(), "Double Attack Target" },
		{ Invincibility().getType(), "Invincibility Target" },
		{ NoGravFieldFX().getType(), "Zero Gravity Target" },
		{ DoubleGravFieldFX().getType(), "Double Gravity Target" },
		{ HalfGravFieldFX().getType(), "Half Gravity Target" }
	};

	return true;
}

void Tutorial_Scene::update(float deltaTime)
{
	// watch for new ball type
	for (int i = 0; i < _game->_ballManager->GetNumberOfBalls(); i++)
	{
		int ballType = _game->_ballManager->GetBallAtIndex(i)->getType();
		auto it = _newBallMessages.find(ballType);
		if (it != _newBallMessages.end())
		{
			Display(it->second);
			_newBallMessages.erase(it);
		}
	}
	// stop the players winning/losing
	for (auto& player : _game->_players)
	{
		const float buffer = 50.0f;
		if (player->getPositionY() < Settings::playerMinY + buffer)
		{
			player->setPositionY(Settings::playerMinY + buffer);
		}
		else if (player->getPositionY() > Settings::playerMaxY - buffer)
		{
			player->setPositionY(Settings::playerMaxY - buffer);
		}
	}
	// watch for new target type
	for (const auto& target : _game->_targets)
	{
		int targetType = target->getType();
		auto it = _newTargetMessages.find(targetType);
		if (it != _newTargetMessages.end())
		{
			Display(it->second);
			_newTargetMessages.erase(it);
		}
	}
	// watch for unpause button press
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
