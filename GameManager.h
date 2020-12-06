#pragma once

#include "../ECS-Light/ECS_L/ECSManager.h"
#include "ResourceManager.h"
#include "Vector2.h"
#include <memory>

using namespace ECS_L;
namespace LightEngine
{
	class GameManager
	{
	public:


		void Setup();
		void RegisterComponents();
		void LoadTextures();

		void UpdateLoop();
		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void Render();

		
		Entity CreateProjectile(Vector2 spawnPosition);
		Entity CreatePlayer();
		Entity CreateEnemy();

	private:

		std::unique_ptr<ECSManager> ecsManager;
		std::unique_ptr<ResourceManager> resourceManager;
		bool quit = false;
		SDL_Event mEvents;
	};
}