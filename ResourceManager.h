#pragma once
#include "WindowResource.h"
#include "Timer.h"
#include "InputResource.h"
class ResourceManager
{
public: 
	ResourceManager() 
	{
		winResource = new WindowResource();
		timer = new Timer;
		inputResource = new InputResource();
		//inputResource = new InputResource();
	};
	Timer* GetTimer()
	{
		return timer;
	}
	WindowResource* winResource;
	Timer* timer;
	InputResource* inputResource;
	void updateTest()
	{
		testTime = testTime+ timer->DeltaTime();
	}
	float testTime = 0;
};

