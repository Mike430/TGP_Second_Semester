#pragma once

#include <unordered_map>
#include <set>
#include "Target.h"
#include "CommonTarget.h"
#include "RareTarget.h"
#include "Invincibility.h"
#include "Double_Attack.h"
#include "DoubleGravFieldFX.h"
#include "HalfGravFieldFX.h"
#include "NoGravFieldFX.h"
using namespace std;

class TargetManager
{
private:
	unordered_map<int, float> _targetChance;//target type -> chance of spawning
	float _totalChance;//sum of chances of enabled targets, divide by this to get actual chance
	set<int> _enabledTargets;
public:
	TargetManager();
	~TargetManager();
	Target* CreateTarget();
	void EnableTarget(int targetType);
};

