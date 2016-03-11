#pragma once

namespace Settings
{
	//Ball physics
	const float gravity = 15 * 60; // was 15 per frame at ~60fps, now framerate independant;
	const float dropRate = -1; // Drops per second, -1 means only drop when previous ball is destroyed
	const float horizontalSpeed = 1500;
	//Targets
	const int targetMinTimeVisible = 3000;
	const int targetMaxTimeVisible = 4000;
	const int targetMinTimeInvisible = 500;
	const int targetMaxTimeInvisible = 3000;
	const float targetSizeCommon = 1.0f;
	const float targetSizeRare = 0.5f;
	//Players
	const float playerMinY = 100;
	const float playerMaxY = 500;
	const float playerRelativeStartY = 0.5f;//amount between min and max
	const float playerRelativeStartX = 530;//distance from centre of screen
}