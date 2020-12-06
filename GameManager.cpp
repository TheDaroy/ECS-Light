#include "GameManager.h"
#include "GameSystems.h"
#include "Components.h"

using namespace LightEngine;

void GameManager::Setup()
{
	ecsManager = std::make_unique<ECSManager>();
	resourceManager = std::make_unique<ResourceManager>();
	RegisterComponents();
	LoadTextures();
	CreatePlayer();
}

void GameManager::RegisterComponents()
{
	ecsManager->AddNewComponentType<GraphicsComponent>();
	ecsManager->AddNewComponentType<TransformComponent>();
	ecsManager->AddNewComponentType<InputComponent>();
	ecsManager->AddNewComponentType<BoxCollider>();
	ecsManager->AddNewComponentType<WeaponComponent>();

	
}

void GameManager::LoadTextures()
{
	resourceManager->winResource->LoadNewTexture("PlayerShip.png", "PlayerShip");
}

void GameManager::UpdateLoop()
{
	while (!quit)
	{

		while (SDL_PollEvent(&mEvents) != 0) {

			if (mEvents.type == SDL_QUIT) {

				quit = true;
			}
		}

		resourceManager->GetTimer()->Update();
		resourceManager->winResource->ClearBackBuffer();
		EarlyUpdate();
		Update();
		LateUpdate();
		Render();
		resourceManager->winResource->Render();
		resourceManager->GetTimer()->Reset();
	}
}

void GameManager::EarlyUpdate()
{
	
}

void GameManager::Update()
{
	Systems::Movement::Update(ecsManager.get(),resourceManager.get());
}

void GameManager::LateUpdate()
{
	Systems::Graphics::Update(ecsManager.get(),resourceManager.get());
}

void GameManager::Render()
{
	
}

Entity GameManager::CreateProjectile(Vector2 spawnPosition)
{
	Entity projectile  = ecsManager->GetNewEntity();
	ecsManager->AddComponentToEntity<GraphicsComponent>(projectile);
	ecsManager->AddComponentToEntity<TransformComponent>(projectile);
	ecsManager->AddComponentToEntity<BoxCollider>(projectile);
	
	
	GraphicsComponent& graphComp = ecsManager->GetComponent<GraphicsComponent>(projectile);
	graphComp.texture = resourceManager->winResource->GetTexture("PlayerShip");
	graphComp.rect.h = 20;
	graphComp.rect.w = 20;
	graphComp.rect.x = 20;
	graphComp.rect.y = 20;

	TransformComponent& transfComp = ecsManager->GetComponent<TransformComponent>(projectile);
	transfComp.position.x = 200;
	transfComp.position.y = 200;
	
	return projectile;
}

Entity GameManager::CreatePlayer()
{
	Entity player = ecsManager->GetNewEntity();
	ecsManager->AddComponentToEntity<GraphicsComponent>(player);
	ecsManager->AddComponentToEntity<TransformComponent>(player);
	ecsManager->AddComponentToEntity<BoxCollider>(player);
	ecsManager->AddComponentToEntity<InputComponent>(player);

	GraphicsComponent& graphComp = ecsManager->GetComponent<GraphicsComponent>(player);
	graphComp.texture = resourceManager->winResource->GetTexture("PlayerShip");
	graphComp.rect.h = 200;
	graphComp.rect.w = 200;
	graphComp.rect.x = 200;
	graphComp.rect.y = 200;


	TransformComponent& transfComp = ecsManager->GetComponent<TransformComponent>(player);
	transfComp.position.x = 0;
	transfComp.position.y = 0;

	return player;
}

