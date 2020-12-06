#pragma once
#include "Rectangle.h"
#include <vector>

typedef void (*OnCollision)();

struct BoxCollider
{
	Vector2 size{ 10.f, 10.f};
	
	uint32_t layer = 1;

	OnCollision onCorrectCollision = nullptr;
};