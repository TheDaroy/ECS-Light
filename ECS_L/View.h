#pragma once


#include "../ECS-Light/ECS_L/ECSManager.h"
#include <cstdint>

namespace ECS_L
{
template<typename...Components>
struct View
{
	ECSManager* manager;
	ComponentSet set;
	Entity nrToitterateTo;
	
	View(ECSManager* _mainManager)
	{
		manager = _mainManager;
		ComponentID compIDs[] = { manager->GetComponentManger()->GetComponentID<Components>()...};
		for (ComponentID id : compIDs)
		{			
			set.set(id);
		}
		nrToitterateTo = manager->GetEntityManager()->GetEntityWithHighestValue()+1;			
	}

	struct iterator
	{
		ECSManager* manager;
		Entity entity;
		ComponentSet set;
		Entity nrToitterateTo;
		iterator(ECSManager* _manager, Entity _entity, ComponentSet _set, Entity highestValueEntity)
		{
			manager = _manager;
			entity = _entity;
			set = _set;		
			nrToitterateTo = highestValueEntity;
		}

		auto operator*()const
		{
			return entity;
		}

		bool operator==(const iterator& other) const
		{
			return entity == other.entity || entity == nrToitterateTo;

		}

		bool operator!=(const iterator& other) const
		{
			return entity != other.entity && entity != nrToitterateTo;
		}

		iterator& operator++()
		{
			do
			{
				entity++; 
			} while ((set & manager->GetEntityManager()->GetEntityComponentSet(entity)) != set && entity < nrToitterateTo);
			
			return *this;
		}
	};


	const iterator begin() const
	{
		std::uint32_t first_index = 0;
		while (first_index < nrToitterateTo && (set & manager->GetEntityManager()->GetEntityComponentSet(first_index)) != set)
		{
			first_index++;			
		}
		return iterator(manager, first_index, set, nrToitterateTo);
	}
	const iterator end() const
	{		
		return iterator(manager, nrToitterateTo, set, nrToitterateTo);
	}
		
	

};
}