#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

GameManager* GameManager::getInstance()
{
	if (!_instance)
	{
		_instance = new GameManager();
	}
	return _instance;
}
