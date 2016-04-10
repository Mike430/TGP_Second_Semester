#pragma once

#include <string>
#include <sstream>
using namespace std;

namespace AudioHelper
{
	string getFileName(string soundEffectName);
	void PreLoad(string soundEffectName);
	void Play(string soundEffectName);
	void PlayRandom(string soundEffectName, int numEffects);
}
