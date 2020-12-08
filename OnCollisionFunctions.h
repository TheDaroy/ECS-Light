#pragma once
#include "ECS_L/ECSManager.h"

namespace  ECS_L::Systems::Collision::OnCollision
{
	void DestroyEntity(ECSManager* manager, Entity entity)
	{
		manager->GetEntityManager()->DestroyEntity(entity);
	}
}