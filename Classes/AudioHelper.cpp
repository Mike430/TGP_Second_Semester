#include "AudioHelper.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void AudioHelper::PreLoad(string soundEffectName)
{
	SimpleAudioEngine::getInstance()->preloadEffect(getFileName(soundEffectName).c_str());
}

void AudioHelper::PreLoad(string soundEffectName, int numEffects)
{
	for (int i = 1; i <= numEffects; i++)
	{
		stringstream fileName;
		fileName << soundEffectName;
		fileName << i;
		PreLoad(fileName.str());
	}
}

void AudioHelper::PreLoadAll()
{
	for (string& sound : vector<string> {
		"airhorn",
		"bombball",
		"endgrav",
		"mainsong",
		"Menusong",
		"missilehit",
		"missilelaunch2",
		"moneyball",
		"normalball",
		"oilball",
		"powderball2",
		"selfexplode",
		"startgrav"
	})
	{
		PreLoad(sound);
	}
	for (pair<string, int>& soundWithVariations : vector<pair<string, int>>{
		{ "AU", 8 },
		{ "bathitting", 4 }
	})
	{
		PreLoad(soundWithVariations.first, soundWithVariations.second);
	}
}

void AudioHelper::Play(string soundEffectName, float pitch, float gain)
{
	SimpleAudioEngine::getInstance()->playEffect(getFileName(soundEffectName).c_str(), false, pitch, 0.0f, gain);
}

void AudioHelper::PlayRandom(string soundEffectName, int numEffects, float pitch, float gain)
{
	stringstream fileName;
	fileName << soundEffectName;
	fileName << int(((double)rand() / (double)RAND_MAX) * numEffects) + 1;
	Play(fileName.str(), pitch, gain);
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
