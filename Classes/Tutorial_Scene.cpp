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
	_messageSprite = _rootNode->getChildByName<Sprite*>("tutorial_sprite");
	_messageBackground = _rootNode->getChildByName<Sprite*>("MessageBackground");
	_resumeButton = _rootNode->getChildByName<Button*>("resume_button");
	_resumeButton->addClickEventListener(CC_CALLBACK_0(Tutorial_Scene::UnPauseGame, this));

	_wasPaused = false;
	SetOverlayVisible(false);

	this->scheduleUpdate();

	_introMessages = list<TutorialMessage>{
		TutorialMessage("welcome 2 tha game"),
		TutorialMessage("tap the screen to swing your bat"),
		TutorialMessage("hit balls at the other player to knock them down"),
		TutorialMessage("hit targets to move up and gain powerups")
	};

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
		{ Invincibility::type, TutorialMessage("Invincibility Target", "res/Sprites/Invincibility.png") },
		{ NoGravFieldFX::type, TutorialMessage("Zero Gravity Target", "res/Sprites/ZeroGrav.png") },
		{ DoubleGravFieldFX::type, TutorialMessage("Double Gravity Target", "res/Sprites/DoubleGrav.png") },
		{ HalfGravFieldFX::type, TutorialMessage("Half Gravity Target", "res/Sprites/HalfGrav.png") }
	};
	_winLoseMessages = unordered_map < int, TutorialMessage > {
		{ -1, TutorialMessage("You would lose at this point because your player is at the bottom") },
		{ 1, TutorialMessage("You would win at this point because your player is at the top") }
	};

	return true;
}

void Tutorial_Scene::update(float deltaTime)
{
	// watch for unpause button press
	if (_wasPaused && !_game->IsPaused())
	{
		OnResumeGame();
	}
	_wasPaused = _game->IsPaused();
	if (_game->IsPaused() || _game->_countDown > 4)
	{
		return;
	}
	if (!_introMessages.empty())
	{
		Display(_introMessages.front());
		_introMessages.pop_front();
	}
	// watch for new ball type
	for (int i = 0; i < _game->_ballManager->GetNumberOfBalls(); i++)
	{
		Ball* ball = _game->_ballManager->GetBallAtIndex(i);
		if (ball->_wayPointIndex >= 2)//visible on screen
		{
			int ballType = ball->getType();
			auto it = _newBallMessages.find(ballType);
			if (it != _newBallMessages.end())
			{
				Display(it->second);
				_newBallMessages.erase(it);
				break;
			}
		}
	}
	// stop the players winning/losing
    if(_game->_countDown <=0)
    {
	for (auto& player : _game->_players)
	{
		int displayWinLoseMessage = 0;
		const float buffer = 50.0f;
		if (player->getPositionY() < Settings::playerMinY + buffer)
		{
			player->setPositionY(Settings::playerMinY + buffer);
			displayWinLoseMessage = -1;
		}
		else if (player->getPositionY() > Settings::playerMaxY - buffer)
		{
			player->setPositionY(Settings::playerMaxY - buffer);
			displayWinLoseMessage = 1;
		}
		if (displayWinLoseMessage != 0)
		{
			auto it = _winLoseMessages.find(displayWinLoseMessage);
			if (it != _winLoseMessages.end())
			{
				Display(it->second);
				_winLoseMessages.erase(it);
			}
		}
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
}

void Tutorial_Scene::Display(TutorialMessage message)
{
	_game->Pause();
	_text->setText(message.message);
	SetOverlayVisible(true);
	if (message.spriteFile == "")
	{
		_messageSprite->setVisible(false);
	}
	else
	{
		_messageSprite->setTexture(message.spriteFile);
	}
}

void Tutorial_Scene::OnResumeGame()
{
	SetOverlayVisible(false);
}

void Tutorial_Scene::UnPauseGame()
{
	_game->UnPause();
}

void Tutorial_Scene::SetOverlayVisible(bool visible)
{
	for (auto& child : getChildren())
	{
		child->setVisible(visible);
	}
}
