#include "AudioHelper.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void AudioHelper::PreLoad(string soundEffectName)
{
	SimpleAudioEngine::getInstance()->preloadEffect(getFileName(soundEffectName).c_str());
}

void AudioHelper::Play(string soundEffectName)
{
	SimpleAudioEngine::getInstance()->playEffect(getFileName(soundEffectName).c_str());
}

void AudioHelper::PlayRandom(string soundEffectName, int numEffects)
{
	stringstream fileName;
	fileName << soundEffectName;
	fileName << int(((double)rand() / (double)RAND_MAX) * numEffects) + 1;
	Play(fileName.str());
}

string AudioHelper::getFileName(string soundEffectName)
{
	string fileName = "res/Audio/" + soundEffectName;
	if (soundEffectName.find('.') == soundEffectName.npos)
	{
		fileName += ".mp3";
	}
	return fileName;
}
