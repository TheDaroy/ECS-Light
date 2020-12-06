#include "GameManager.h"

int main(int argc, char* argv[])
{
	
	LightEngine::GameManager manger;
	manger.Setup();
	
	manger.UpdateLoop();
	return 0;
};