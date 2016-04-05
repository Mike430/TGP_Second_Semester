#include "AudioHelper.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void AudioHelper::Play(const string soundEffectName)
{
	SimpleAudioEngine::getInstance()->playEffect(("res/Audio/" + soundEffectName + ".mp3").c_str());
}
