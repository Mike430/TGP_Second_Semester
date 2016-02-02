#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

GameManager* GameManager::getInstance()
{
	if (!instance)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::init(Node* rootNode)
{
	const string path = "res/";
	const float y = 250;
	const float centerX = Director::getInstance()->getVisibleSize().width / 2;
	const float relativeX = 500;
	for (const auto& p : vector<pair<string, Vec2>>{ { "PlayerLeft.csb", { -1, 0 } }, { "PlayerRight.csb", { 1, 0 } } })
	{
		players.push_back(Player::create(path + p.first, Vec2(centerX + relativeX * p.second.x, y)));
		rootNode->addChild(players.back());
	}
}

