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
	_messageSprite = _rootNode->getChildByName<Sprite*>("tutorial_sprite");
	_messageSprite->setVisible(false);

	_wasPaused = false;

	this->scheduleUpdate();

	_newBallMessages = unordered_map<int, TutorialMessage>{
		{ RocketBall::type, TutorialMessage("Rocket Ball", "res/Sprites/RocketBall.png") },
		{ OilBall::type, TutorialMessage("Oil Ball", "res/OilBall.png") },
		{ BombBall::type, TutorialMessage("Bomb Ball", "res/Sprites/bombBall.png") },
		{ BombOther::type, TutorialMessage("Bomb Other Ball", "res/otherBombBall.png") },
		{ WalletBall::type, TutorialMessage("Wallet Ball", "res/Wallet.png") },
		{ PowderBall::type, TutorialMessage("Powder Ball", "res/PowderBall.png") }
	};
	_newTargetMessages = unordered_map<int, TutorialMessage>{
		{ RareTarget::type, TutorialMessage("Rare Target", "res/Sprites/rare.png") },
		{ Double_Attack::type, TutorialMessage("Double Attack Target", "res/Sprites/DoubleAttack.png") },
		{ Invincibility::type, TutorialMessage("Invincibility Target", "res/Sprites/Invinsibility.png") },
		{ NoGravFieldFX::type, TutorialMessage("Zero Gravity Target", "res/Sprites/ZeroGrav.png") },
		{ DoubleGravFieldFX::type, TutorialMessage("Double Gravity Target", "res/Sprites/DoubleGrav.png") },
		{ HalfGravFieldFX::type, TutorialMessage("Half Gravity Target", "res/Sprites/HalfGrav.png") }
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

void Tutorial_Scene::Display(TutorialMessage message)
{
	_game->Pause();
	_text->setText(message.message);
	_text->setVisible(true);
	_messageSprite->setTexture(message.spriteFile);
	_messageSprite->setVisible(true);
}

void Tutorial_Scene::OnResumeGame()
{
	_text->setVisible(false);
	_messageSprite->setVisible(false);
}
