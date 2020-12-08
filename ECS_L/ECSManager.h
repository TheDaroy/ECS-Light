#pragma once


#include "ComponentManager.h"
#include "EntityManager.h"



namespace ECS_L
{
	/*
	This Class Acts as a coordinator between the EntityManager and ComponentManager.
	It only exists for convenience, and can be excluded if you want to use the two managers directly. 
	*/
	class ECSManager
	{

	public:
		ECSManager()
		{
			
			componentManager = std::make_unique<ComponentManager>();
			entityManager = std::make_unique<EntityManager>();
		}
		ComponentManager* GetComponentManger()
		{
			return componentManager.get();
		}
		EntityManager* GetEntityManager()
		{
			return entityManager.get();
		}

		Entity GetNewEntity()
		{
			return entityManager->GetNewEntity();
		}
		void DestroyEntity(Entity entity)
		{
			entityManager->DestroyEntity(entity);
		}
		template<typename T>
		void AddComponentToEntity(Entity entity)
		{
			entityManager->AddComponentToEntity(componentManager->GetComponentID<T>(),entity);
		}
		template<typename T>
		T& GetComponent(Entity entity)
		{
			return componentManager->GetComponent<T>(entity);
		}
		template<typename T>
		void AddNewComponentType()
		{
			componentManager->AddNewComponentType<T>();
		}
	private:
		
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<EntityManager> entityManager;

	};
}