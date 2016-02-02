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
	void init(Node* rootNode);
private:
	static GameManager* instance;
	vector<Player*> players;
};

