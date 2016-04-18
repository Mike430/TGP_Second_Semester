#include "AnimationHelper.h"

unordered_map<string, AnimationHelper::AnimData> AnimationHelper::animations;
unordered_map<string, AnimLoadData> AnimationHelper::animationLoadData;

void AnimationHelper::PreLoadAnimation(string name, int numFrames, int FrameX, int FrameY, float framerate, string namePrefix, string fileType)
{
	if (animations.find(name) == animations.end())
	{
		LoadAnimation(name, numFrames, FrameX, FrameY, framerate, namePrefix, fileType);
	}
	AnimLoadData loadData;
	loadData.frames = numFrames;
	loadData.width = FrameX;
	loadData.height = FrameY;
	loadData.frameRate = framerate;
	loadData.namePrefix = namePrefix;
	loadData.fileType = fileType;
	animationLoadData[name] = loadData;
}

void AnimationHelper::UnLoadAnimation(string animationName)
{
	animations.erase(animationName);
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

void AnimationHelper::LoadAnimation(string name, int numFrames, int FrameX, int FrameY, float framerate, string namePrefix, string fileType)
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
		string file = path + namePrefix + pad + index + fileType;
		frames.pushBack(SpriteFrame::create(file, Rect(0, 0, FrameX, FrameY)));
	}
	animation.frameRate = framerate;
	animations[name] = animation;
}

cocos2d::Animate* AnimationHelper::CreateAnimate(string animationName, bool loop)
{
	auto it = animations.find(animationName);
	if (it == animations.end())
	{
		//animation not found, maybe unloaded
		auto loadDataIt = animationLoadData.find(animationName);
		if (loadDataIt != animationLoadData.end())
		{
			AnimLoadData& d = loadDataIt->second;
			LoadAnimation(animationName, d.frames, d.width, d.height, d.frameRate, d.namePrefix, d.fileType);
			it = animations.find(animationName);
		}
	}
	if (it == animations.end())
	{
		throw runtime_error("animation not found");
	}
	AnimData* animData = &animations[animationName];
	float delay = 1.0f / animData->frameRate;
	unsigned int loops = loop ? numeric_limits<unsigned int>::max() : 1;
	Animation* animation = Animation::createWithSpriteFrames(animData->frames, delay, loops);
	return Animate::create(animation);
}
