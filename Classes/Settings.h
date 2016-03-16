#pragma once

namespace Settings
{
	//Ball physics
	const float gravity = 15 * 60; // was 15 per frame at ~60fps, now framerate independant;
	const float dropRate = -1; // Drops per second, -1 means only drop when previous ball is destroyed
	const float horizontalSpeed = 1500;
	//Targets
	const float targetMinSpawnDelay = 0.5f;
	const float targetMaxSpawnDelay = 3.0f;
	const float targetLifeTime = 4.0f;
	//Players
	const float playerMinY = 150;
	const float playerMaxY = 500;
	const float playerStartY = 300;
	const float playerRelativeStartX = 530;//distance from centre of screen
	const float playerSeeSawMoveDistance = 9;
	const float playerDazeRecoveryTime = 0.5f;
	const float playerDazeInvincibilityTime = 3.0f;
	//Field Effects
	const float ZeroGravityFieldDuration = 5;
	const float HalfGravityFieldDuration = 10;
	const float DoubleGravityFieldDuration = 15;
	const float HalfGravityStrength = 0.8;  // _gravity = _gravity * Settings::HalfGravityStrength; <- how its calculated
	const float DoubleGravityStrength = 2; // _gravity = _gravity * Settings::DoubleGravityStrength;
}