#include "AnimationHelper.h"

unordered_map<string, AnimationHelper::AnimData> AnimationHelper::animations;

void AnimationHelper::PreLoadAnimation(string name, int numFrames, float framerate)
{
	if (animations.find(name) == animations.end())
	{
		LoadAnimation(name, numFrames, framerate);
	}
}

void AnimationHelper::Animate(Sprite* sprite, string animationName, bool loop)
{
	sprite->stopAllActions();
	sprite->runAction(CreateAnimate(animationName, loop));
}

bool AnimationHelper::AnimationFinished(Sprite* sprite)
{
	return sprite->getNumberOfRunningActions() == 0;
}

void AnimationHelper::LoadAnimation(string name, int numFrames, float framerate)
{
	AnimData animation;
	Vector<SpriteFrame*>& frames = animation.frames;
	frames.reserve(numFrames);
	for (int i = 1; i <= numFrames; i++)
	{
		stringstream indexStream;
		indexStream << i;
		string index = indexStream.str();
		//pad with '0' to length of 4
		string pad = string(4 - index.length(), '0');
		string path = "res/Animations/" + name + "/";
		string fileType = ".png";
		string file = path + pad + index + fileType;
		frames.pushBack(SpriteFrame::create(file, Rect(0, 0, 300, 225)));
	}
	animation.frameRate = framerate;
	animations[name] = animation;
}

cocos2d::Animate* AnimationHelper::CreateAnimate(string animationName, bool loop)
{
	AnimData* animData = &animations[animationName];
	float delay = 1.0f / animData->frameRate;
	unsigned int loops = loop ? numeric_limits<unsigned int>::max() : 1;
	Animation* animation = Animation::createWithSpriteFrames(animData->frames, delay, loops);
	return Animate::create(animation);
}
