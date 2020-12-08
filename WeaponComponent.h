#pragma once
#include <SDL_image.h>
#include "Vector2.h"


struct WeaponComponent
{
	float fireRate = 50;
	float fireTimer = 0;

	Vector2 firePositionOffset;

	bool fire = false;

	
	// MUCH TEMP VERY TEST WOOOW
};

