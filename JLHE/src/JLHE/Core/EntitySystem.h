#pragma once

#include "JLHE/Core/Entity.h"
#include "JLHE/Core/Timestep.h"
#include "JLHE/Events/Event.h"

namespace JLHE {

	class EntitySystem {
	public:
		EntitySystem();
		virtual ~EntitySystem();

		void OnUpdate(Timestep& ts);
		void OnEvent(Event& e);
		void OnRender();

		bool AddEntity(Entity* entity);
		bool RemoveEntity(Entity* entity);
	private:
		std::vector<Entity*> m_Entities;
		static const uint32_t s_MaxEntities = 100;
	};

}