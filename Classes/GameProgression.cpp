#include "GameProgression.h"
#include "Game_Scene.h"

GameProgression::GameProgression(Game_Scene* game)
	: _game(game)
{
	auto enableBall = [this](int ballType) {
		return function<void()>([this, ballType]() {
			EnableBall(ballType);
		});
	};
	auto enableTarget = [this](int targetType) {
		return function<void()>([this, targetType]() {
			EnableTarget(targetType);
		});
	};
	_events = vector<pair<float, function<void()>>> {
		{ 2, enableBall(RocketBall::type) },
		{ 10, enableBall(OilBall::type) },
		{ 20, enableBall(BombBall::type) },
		{ 30, enableBall(BombOther::type) },
		{ 40, enableBall(WalletBall::type) },
		{ 50, enableBall(PowderBall::type) },
		{ 5, enableTarget(RareTarget::type) },
		{ 15, enableTarget(Double_Attack::type) },
		{ 25, enableTarget(Invincibility::type) },
		{ 35, enableTarget(NoGravFieldFX::type) },
		{ 45, enableTarget(DoubleGravFieldFX::type) },
		{ 55, enableTarget(HalfGravFieldFX::type) }
	};
}

GameProgression::~GameProgression()
{
}

void GameProgression::Update(float deltaTime)
{
	_currentTime += deltaTime;
	for (auto it = _events.begin(); it != _events.end() && !_events.empty(); it++)
	{
		float eventTriggerTime = it->first;
		auto& func = it->second;
		if (_currentTime >= eventTriggerTime)
		{
			func();
			_events.erase(it);
			break;
		}
	}
}

void GameProgression::EnableBall(int ballType)
{
	_game->_ballManager->EnableBall(ballType);
}

void GameProgression::EnableTarget(int targetType)
{
	_game->_targetManager->EnableTarget(targetType);
}

int GameProgression::GetRemainingEvents()
{
	return _events.size();
}
