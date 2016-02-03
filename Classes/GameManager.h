#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <vector>
#include "Player.h"
USING_NS_CC;
using namespace std;

class GameManager
{
public:
	GameManager();
	~GameManager();
	static GameManager* getInstance();
private:
	static GameManager* _instance;
};

