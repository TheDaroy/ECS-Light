#include "GameManager.h"
#include "GameSystems.h"
#include "Components.h"
#include "OnCollisionFunctions.h"


using namespace LightEngine;

void GameManager::Setup()
{
	ecsManager = std::make_unique<ECSManager>();
	resourceManager = std::make_unique<ResourceManager>();
	collisionLayerManager = std::make_unique<CollisionLayerManager>();

	RegisterComponents();
	LoadTextures();
	SetCollisionLayers();
	CreatePlayer();
	CreateEnemy();
}

void GameManager::RegisterComponents()
{
	ecsManager->AddNewComponentType<GraphicsComponent>();
	ecsManager->AddNewComponentType<TransformComponent>();
	ecsManager->AddNewComponentType<InputComponent>();
	ecsManager->AddNewComponentType<BoxCollider>();
	ecsManager->AddNewComponentType<WeaponComponent>();
	ecsManager->AddNewComponentType<PlayerComponent>();
	ecsManager->AddNewComponentType<ProjectileComponent>();
	ecsManager->AddNewComponentType<EnemyComponent>();
	
}

void GameManager::LoadTextures()
{
	resourceManager->winResource->LoadNewTexture("PlayerShip.png", "PlayerShip");
}


void GameManager::SetCollisionLayers()
{
	collisionLayerManager->AddCollisionToLayer(0, { 1,2,3 });
	collisionLayerManager->AddCollisionToLayer(1, { 0,2,3 });
	collisionLayerManager->AddCollisionToLayer(2, { 0,1,3 });
	collisionLayerManager->AddCollisionToLayer(3, { 0,1,2 });
}
void GameManager::UpdateLoop()
{
	while (!quit)
	{
		resourceManager->GetTimer()->Update();
		
		while (SDL_PollEvent(&mEvents)) {
			
			if (mEvents.type == SDL_QUIT) {

				quit = true;
			}
		}

		resourceManager->GetTimer()->Reset();
		EarlyUpdate();
		Update();
		LateUpdate();
		resourceManager->winResource->Render();
	}
}

void GameManager::EarlyUpdate()
{
	
	resourceManager->winResource->ClearBackBuffer();
	resourceManager->inputResource->Update();
}

void GameManager::Update()
{
	Systems::Player::Update(ecsManager.get(),resourceManager.get());
	Systems::Enemy::Update(ecsManager.get(), resourceManager.get());
	Systems::Weapon::Update(ecsManager.get(), resourceManager.get());
	Systems::Projectile::Update(ecsManager.get(), resourceManager.get());

}

void GameManager::LateUpdate()
{
	Systems::Collision::Update(ecsManager.get(),resourceManager.get(),collisionLayerManager->GetCollisionDataArray());
	Systems::Graphics::Update(ecsManager.get(),resourceManager.get());
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
	ecsManager->AddComponentToEntity<PlayerComponent>(player);
	ecsManager->AddComponentToEntity<WeaponComponent>(player);

	GraphicsComponent& graphComp = ecsManager->GetComponent<GraphicsComponent>(player);
	graphComp.texture = resourceManager->winResource->GetTexture("PlayerShip");
	graphComp.rect.h = 200;
	graphComp.rect.w = 200;
	graphComp.rect.x = 200;
	graphComp.rect.y = 200;


	TransformComponent& transfComp = ecsManager->GetComponent<TransformComponent>(player);
	transfComp.position.x = 0;
	transfComp.position.y = 0;

	BoxCollider& boxComp = ecsManager->GetComponent<BoxCollider>(player);
	boxComp.layer = 0;
	boxComp.size.x = 100;
	boxComp.size.y = 100;
	//boxComp.onCorrectCollision = ECS_L::Systems::Collision::OnCollision::DestroyEntity;
	
	PlayerComponent& playerComp = ecsManager->GetComponent<PlayerComponent>(player);
	playerComp.MoveSpeed = 0.5f;

	WeaponComponent& weaponComp = ecsManager->GetComponent<WeaponComponent>(player);
	weaponComp.firePositionOffset = {0,-50};

	return player;
}

Entity GameManager::CreateEnemy()
{
	Entity enemy = ecsManager->GetNewEntity();
	ecsManager->AddComponentToEntity<GraphicsComponent>(enemy);
	ecsManager->AddComponentToEntity<TransformComponent>(enemy);
	ecsManager->AddComponentToEntity<BoxCollider>(enemy);
	ecsManager->AddComponentToEntity<EnemyComponent>(enemy);

	GraphicsComponent& graphComp = ecsManager->GetComponent<GraphicsComponent>(enemy);
	graphComp.texture = resourceManager->winResource->GetTexture("PlayerShip");
	graphComp.rect.h = 200;
	graphComp.rect.w = 200;
	graphComp.rect.x = 200;
	graphComp.rect.y = 200;


	TransformComponent& transfComp = ecsManager->GetComponent<TransformComponent>(enemy);
	transfComp.position.x = 200;
	transfComp.position.y = 0;

	BoxCollider& boxComp = ecsManager->GetComponent<BoxCollider>(enemy);
	boxComp.layer = 1;
	boxComp.size.x  = 100;
	boxComp.size.y = 100;


	return enemy;
}



void GameManager::PlayerStuff()
{

}