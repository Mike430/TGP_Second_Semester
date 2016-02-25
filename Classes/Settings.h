#pragma once

namespace Settings
{
	const float gravity = 15 * 60; // was 15 per frame at ~60fps, now framerate independant;
	const float dropRate = -1; // Drops per second, -1 means only drop when previous ball is destroyed
	const float horizontalSpeed = 0;
	const float targetSpawnRate = 0;
	const float targetSizeCommon = 0;
	const float targetSizeRare = targetSizeCommon;
}