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
	const float powerUpTime = 30.0f;
}