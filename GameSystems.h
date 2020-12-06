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
	namespace // private collision functions
	{
		bool BoxVsBox(const BoxCollider& rect1, const TransformComponent& pos1, const BoxCollider& rect2, const TransformComponent& pos2)
		{
			return (pos1.position.x < pos2.position.x + rect2.size.x
				&& pos1.position.x + rect1.size.x > pos2.position.x

				&& pos1.position.y < pos2.position.y + rect2.size.y
				&& pos1.position.y + rect1.size.y > pos2.position.y);
		}
	}
	void Update(ECSManager* manager, ResourceManager* resManager)
	{
		auto view = View<TransformComponent, BoxCollider>(manager);
		std::vector<Entity> entetiesToRemove;

		for (auto entity : view)
		{
			TransformComponent& transformComp = manager->GetComponentManger()->GetComponent<TransformComponent>(entity);
			BoxCollider& colliderComp = manager->GetComponentManger()->GetComponent<BoxCollider>(entity);

			for (auto otherEntity : view)
			{
				if (otherEntity == entity)
				{
					continue;
				}

				TransformComponent& otherTransformComp = manager->GetComponentManger()->GetComponent<TransformComponent>(otherEntity);
				BoxCollider& otherColliderComp = manager->GetComponentManger()->GetComponent<BoxCollider>(otherEntity);


				if (BoxVsBox(colliderComp, transformComp, otherColliderComp, otherTransformComp))
				{

					std::cout << entity << " Colliding with " << otherEntity << std::endl;
				}
			}
		}
	}


}
namespace ECS_L::Systems::Movement
{
	void Update(ECSManager* manager, ResourceManager* resManager)
	{
		auto view = View<InputComponent, TransformComponent>(manager);

		for (auto entity : view)
		{
			TransformComponent& transfromComp = manager->GetComponentManger()->GetComponent<TransformComponent>(entity);
			InputComponent& inputComp = manager->GetComponentManger()->GetComponent<InputComponent>(entity);
			//std::cout << transfromComp.x << " : " << transfromComp.y<< std::endl;
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_W))
			{
				//std::cout << "Right" << std::endl;
				transfromComp.position.y -= 2.f * resManager->timer->DeltaTime();
			}
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_S))
			{
				//std::cout << "Left" << std::endl;
				transfromComp.position.y += 2.f * resManager->timer->DeltaTime();
			}
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_A))
			{
				//std::cout << "Up" << std::endl;
				transfromComp.position.x -=2.f * resManager->timer->DeltaTime();
			}
			if (resManager->inputResource->KeyDown(SDL_SCANCODE_D))
			{
				//std::cout << "Down" << std::endl;
				transfromComp.position.x +=2.f * resManager->timer->DeltaTime();
			}

		}
	}
}
//
//class GameManager;
//namespace ECSLight::Systems::Shooting
//{
//	void Update(ECSManager* manager, ResourceManager* resManager, GameManager* gameManager)
//	{
//		
//		auto view = View<WeaponComponent, TransformComponent>(manager);
//		for (auto entity : view)
//		{
//			WeaponComponent& wc = manager->GetcomponentManger()->GetComponent<WeaponComponent>(entity);
//			
//			if (wc.fireTimer <= 0 && resManager->inputResource->KeyDown(SDL_SCANCODE_SPACE))
//			{
//				
//				wc.fireTimer = wc.fireRate;
//				TransformComponent& tc = manager->GetcomponentManger()->GetComponent<TransformComponent>(entity);
//
//				
//			}
//		}
//	}
//}