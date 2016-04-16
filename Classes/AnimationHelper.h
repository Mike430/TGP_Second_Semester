#pragma once

#include <unordered_map>
#include <sstream>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
using namespace std;
using namespace cocos2d;

class AnimationHelper
{
public:
	static void PreLoadAnimation(string name, int numFrames, float framerate = 60.0f, string namePrefix = "", string fileType = ".png");
	static void Animate(Sprite* sprite, string animationName, bool loop = false);
	static bool AnimationFinished(Sprite* sprite);
private:
	struct AnimData { Vector<SpriteFrame*> frames; float frameRate; };
	static unordered_map<string, AnimData> animations;
	static void LoadAnimation(string name, int numFrames, float framerate, string namePrefix = "", string fileType = ".png");
	static cocos2d::Animate* CreateAnimate(string animationName, bool loop);
};

