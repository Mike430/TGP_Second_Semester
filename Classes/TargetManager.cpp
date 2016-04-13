#include "TargetManager.h"


TargetManager::TargetManager()
{
	_targetChance = unordered_map<int, float>{
		{ CommonTarget::type, 70.0f },
		{ RareTarget::type, 6.0f },
		{ Double_Attack::type, 7.0f },
		{ Invincibility::type, 3.0f },
		{ HalfGravFieldFX::type, 4.0f },
		{ DoubleGravFieldFX::type, 4.0f },
		{ NoGravFieldFX::type, 6.0f }
	};
	EnableTarget(CommonTarget::type);
}


TargetManager::~TargetManager()
{
}

Target* TargetManager::CreateTarget()
{
	//or would you prefer templates?
	static const auto createTargetFromType = [](int type)
	{
		Target* newBall = nullptr;
		switch (type)
		{
		case CommonTarget::type:		newBall = CommonTarget::create(); break;
		case RareTarget::type:			newBall = RareTarget::create(); break;
		case Double_Attack::type:		newBall = Double_Attack::create(); break;
		case Invincibility::type:		newBall = Invincibility::create(); break;
		case DoubleGravFieldFX::type:	newBall = DoubleGravFieldFX::create(); break;
		case NoGravFieldFX::type:		newBall = NoGravFieldFX::create(); break;
		case HalfGravFieldFX::type:		newBall = HalfGravFieldFX::create(); break;
		}
		return newBall;
	};
	//random enabled target based on chances
	int targetType = 0;
	float rnd = RandomHelper::random_real(0.0f, _totalChance);
	for (const auto enabledType : _enabledTargets)
	{
		float chance = _targetChance[enabledType];
		if (rnd <= chance)
		{
			targetType = enabledType;
			break;
		}
		rnd -= chance;
	}
	//create new ball
	Target* newTarget = createTargetFromType(targetType);
	//AddBall(parent, newBall);
	return newTarget;
}

void TargetManager::EnableTarget(int targetType)
{
	_enabledTargets.insert(targetType);
	_totalChance += _targetChance[targetType];
}
