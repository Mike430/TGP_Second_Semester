#include "TargetManager.h"
#include "Game_Scene.h"

TargetManager::TargetManager()
{
    auto common = CommonTarget::type;
    auto rare = RareTarget::type;
    auto doublePower = Double_Attack::type;
    auto invincibility = Invincibility::type;
    auto halfGrav = HalfGravFieldFX::type;
    auto doublegrav = DoubleGravFieldFX::type;
    auto noGrav = NoGravFieldFX::type;
	_targetChance = unordered_map<int, float>{
		{ common, 70.0f },
		{ rare, 6.0f },
		{ doublePower, 7.0f },
		{ invincibility, 3.0f },
		{ halfGrav, 4.0f },
		{ doublegrav, 4.0f },
		{ noGrav, 6.0f }
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
        const auto common = CommonTarget::type;
        const auto rare = RareTarget::type;
        const auto doublePower = Double_Attack::type;
        const auto invincibility = Invincibility::type;
        const auto halfGrav = HalfGravFieldFX::type;
        const auto doublegrav = DoubleGravFieldFX::type;
        const auto noGrav = NoGravFieldFX::type;
		switch (type)
		{
		case common:		newBall = CommonTarget::create(); break;
		case rare:			newBall = RareTarget::create(); break;
		case doublePower:		newBall = Double_Attack::create(); break;
		case invincibility:		newBall = Invincibility::create(); break;
		case halfGrav:	newBall = DoubleGravFieldFX::create(); break;
		case doublegrav:		newBall = NoGravFieldFX::create(); break;
		case noGrav:		newBall = HalfGravFieldFX::create(); break;
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
