#pragma once

#include <string>
#include <sstream>
#include <random>
using namespace std;

namespace AudioHelper
{
	string getFileName(string soundEffectName);
	void PreLoad(string soundEffectName);
	void PreLoad(string soundEffectName, int numEffects);
	void PreLoadAll();
	void Play(string soundEffectName, float pitch = 1.0f, float gain = 1.0f);
	void PlayRandom(string soundEffectName, int numEffects, float pitch = 1.0f, float gain = 1.0f);
}
