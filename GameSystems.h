#pragma once
#include "../ECS-Light/ECS_L/View.h"
#include "ResourceManager.h"
#include "Components.h"

namespace ECS_L::Systems::Graphics
{
	void Update(ECSManager* manager, ResourceManager* resManager)
	{
		auto view = View<GraphicsComponent, TransformComponent>(manager);


		for (auto entity : view)
		{
			GraphicsComponent& comp = manager->GetComponentManger()->GetComponent<GraphicsComponent>(entity);
			TransformComponent& transformComp = manager->GetComponentManger()->GetComponent<TransformComponent>(entity);
			comp.rect.x = (int)(transformComp.position.x - 200 * 0.5f);
			comp.rect.y = (int)(transformComp.position.y - 200 * 0.5f);
			resManager->winResource->DrawTexture(comp.texture, NULL, &comp.rect, 0.f, SDL_FLIP_NONE);

		}
	}

}

#include "BoxCollider.h"
namespace ECS_L::Systems::Collision
{
	namespace 
	{
		bool BoxVsBox(const BoxCollider& rect1, const TransformComponent& pos1, const BoxCollider& rect2, const TransformComponent& pos2)
		{
			return (pos1.position.x < pos2.position.x + rect2.size.x
				&& pos1.position.x + rect1.size.x > pos2.position.x

				&& pos1.position.y < pos2.position.y + rect2.size.y
				&& pos1.position.y + rect1.size.y > pos2.position.y);
		}
	}
	void Update(ECSManager* manager, ResourceManager* resManager, const std::array<CollisionSet,COLLISION_LAYER_AMOUNT> collisionDataArray)
	{
		
		auto view = View<TransformComponent, BoxCollider>(manager);

		std::vector<Entity> entetiesToRemove;

		for (auto entity : view)
		{
			TransformComponent& transformComp = manager->GetComponentManger()->GetComponent<TransformComponent>(entity);
			BoxCollider& colliderComp = manager->GetComponentManger()->GetComponent<BoxCollider>(entity);

			colliderComp.collisionData.clear();
			colliderComp.hit = false;

			for (auto otherEntity : view)
			{
				if (otherEntity == entity )
				{
					continue;
				}
				TransformComponent& otherTransformComp = manager->GetComponentManger()->GetComponent<TransformComponent>(otherEntity);
				BoxCollider& otherColliderComp = manager->GetComponentManger()->GetComponent<BoxCollider>(otherEntity);
				if (collisionDataArray[colliderComp.layer][otherColliderComp.layer] == true)
				{
					if (BoxVsBox(colliderComp, transformComp, otherColliderComp, otherTransformComp))
					{
						colliderComp.hit = true;
						CollisionData newData;
						newData.entityHit = otherEntity;
						colliderComp.collisionData.push_back(newData);													
					}

				}
			}
		}
	}


}


namespace ECS_L::Systems::Projectile
{
	namespace
	{
		bool OnCollision(BoxCollider& collider, Entity projectile)
		{
			if (collider.hit)
			{
				return true;// destroy
			}
			return false;
		}
		void Move(TransformComponent& transform, ProjectileComponent& projectileComp, ResourceManager* resManager)
		{
			transform.position += projectileComp.directionToGo * projectileComp.speed * resManager->timer->DeltaTime();
		}
	}

	void Update(ECSManager* manager, ResourceManager* resManager)
	{
		auto view = View<ProjectileComponent>(manager);
		for (auto entity : view)
		{
			TransformComponent& transfComponent = manager->GetComponent<TransformComponent>(entity);
			BoxCollider& colliderComp = manager->GetComponent<BoxCollider>(entity);
			ProjectileComponent& projectileComp = manager->GetComponent<ProjectileComponent>(entity);

			if (OnCollision(colliderComp, entity))
			{
				colliderComp.hit = false;
				colliderComp.collisionData.clear();
				manager->DestroyEntity(entity);
				continue;
			}
			
			Move(transfComponent, projectileComp, resManager);
			
		}
	}

}
namespace ECS_L::Systems::Enemy
{	
	bool OnCollision(BoxCollider& collider)
	{
		if (collider.hit)
		{
			return true;// destroy
		}
		return false;
	}
	void Update(ECSManager* manager, ResourceManager* resManager)
	{
		auto view = View<EnemyComponent>(manager);
		for (auto entity : view)
		{
		BoxCollider& colliderComp = manager->GetComponent<BoxCollider>(entity);
		if (OnCollision(colliderComp))
		{
			colliderComp.hit = false;
			colliderComp.collisionData.clear();
			manager->DestroyEntity(entity);
			continue;
		}
		}
	}
}
namespace ECS_L::Systems::Player
{
	namespace
	{
		bool OnCollision(BoxCollider& collider)
		{
			if (collider.hit)
			{
				return true;// destroy
			}
			return false;
		}
		void Move(TransformComponent& transform, PlayerComponent& playerComp, ResourceManager* resManager)
		{
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_W))
			{
				//std::cout << "Right" << std::endl;
				transform.position.y -= playerComp.MoveSpeed * resManager->timer->DeltaTime();
			}
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_S))
			{
				//std::cout << "Left" << std::endl;
				transform.position.y += playerComp.MoveSpeed * resManager->timer->DeltaTime();
			}
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_A))
			{
				//std::cout << "Up" << std::endl;
				transform.position.x -= playerComp.MoveSpeed * resManager->timer->DeltaTime();
			}
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_D))
			{
				//std::cout << "Down" << std::endl;
				transform.position.x += playerComp.MoveSpeed * resManager->timer->DeltaTime();
			}
		}
		void Shoot(ResourceManager* resManager, WeaponComponent& weaponComp)
		{
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_SPACE) && weaponComp.fireTimer <= 0)
			{
				weaponComp.fire = true;
			}
		}
	}
	void Update(ECSManager* manager, ResourceManager* resManager)
	{
		auto view = View<PlayerComponent>(manager);
		for (auto entity : view)
		{
			BoxCollider& colliderComp = manager->GetComponent<BoxCollider>(entity);
			if (OnCollision(colliderComp))
			{
				colliderComp.hit = false;
				colliderComp.collisionData.clear();
				manager->DestroyEntity(entity);
				continue;
			}
			TransformComponent& transfComponent = manager->GetComponent<TransformComponent>(entity);
			PlayerComponent& playerComp = manager->GetComponent<PlayerComponent>(entity);
			WeaponComponent& weaponComp = manager->GetComponent<WeaponComponent>(entity);

			Move(transfComponent,playerComp,resManager);
			Shoot(resManager, weaponComp);
		}
	}
}


namespace ECS_L::Systems::Weapon
{
	namespace
	{
		void SpawnBullet(ECSManager* manager, ResourceManager* resManager,WeaponComponent& weaponComp, TransformComponent& weaponTransfrom)
		{
			
			Entity projectile = manager->GetNewEntity();
			manager->AddComponentToEntity<GraphicsComponent>(projectile);
			manager->AddComponentToEntity<TransformComponent>(projectile);
			manager->AddComponentToEntity<BoxCollider>(projectile);
			manager->AddComponentToEntity<ProjectileComponent>(projectile);

			GraphicsComponent& graphicsComp = manager->GetComponent<GraphicsComponent>(projectile);
			graphicsComp.texture = resManager->winResource->GetTexture("PlayerShip");
			graphicsComp.rect.h = 20;
			graphicsComp.rect.w = 20;
			graphicsComp.rect.x = 20;
			graphicsComp.rect.y = 20;

			BoxCollider& boxCollider = manager->GetComponent<BoxCollider>(projectile);
			boxCollider.size.x = 20;
			boxCollider.size.y = 20;

			ProjectileComponent& projectileComp = manager->GetComponent<ProjectileComponent>(projectile);
			projectileComp.directionToGo.y = -1;
			projectileComp.directionToGo.x = 0;
			projectileComp.speed = 1.5;

			TransformComponent& transfComp = manager->GetComponent<TransformComponent>(projectile);
			transfComp.position = weaponComp.firePositionOffset + weaponTransfrom.position;
			
			
		}
	}
	void Update(ECSManager* manager, ResourceManager* resManager)
	{
		auto view = View<WeaponComponent>(manager);
		for (auto entity : view)
		{
			WeaponComponent& weaponComp = manager->GetComponent<WeaponComponent>(entity);
			TransformComponent& transfComp = manager->GetComponent<TransformComponent>(entity);
			if (weaponComp.fireTimer >= 0)
			{
				weaponComp.fireTimer -= resManager->GetTimer()->DeltaTime();
			}
			if (weaponComp.fire && weaponComp.fireTimer <= 0)
			{
				SpawnBullet(manager, resManager,weaponComp,transfComp);
				weaponComp.fireTimer = weaponComp.fireRate;
			}
			
			weaponComp.fire = false;
		}
	}
}