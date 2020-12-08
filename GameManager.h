#pragma once

#include "../ECS-Light/ECS_L/ECSManager.h"
#include "ResourceManager.h"
#include "Vector2.h"
#include <memory>
#include "CollisionSettings.h"
#include <SDL_events.h>


using namespace ECS_L;
namespace LightEngine
{
	class GameManager
	{
	public:


		void Setup();
		void RegisterComponents();
		void LoadTextures();
		void SetCollisionLayers();

		void UpdateLoop();
		void EarlyUpdate();
		void Update();
		void LateUpdate();
		

		
		Entity CreateProjectile(Vector2 spawnPosition);
		Entity CreatePlayer();
		Entity CreateEnemy();

		void PlayerStuff();
	private:

		
		std::unique_ptr<ECSManager> ecsManager;
		std::unique_ptr<ResourceManager> resourceManager;
		std::unique_ptr<CollisionLayerManager> collisionLayerManager;

		bool quit = false;
		SDL_Event mEvents;

		
	};
}