#pragma once
#include "JLHE.h"

namespace Arcade {

	class Bullet;

	class Player : public JLHE::Entity {
	public:
		Player(glm::vec3 position, glm::vec2 size, float speed, JLHE::EntitySystem& entitySystem, std::vector<Bullet*>& bullets);

		virtual void OnUpdate(JLHE::Timestep& ts) override;

		void Fire();
	private:
		JLHE::EntitySystem& m_OccupiedEntitySystem;
		std::vector<Bullet*>& m_Bullets;
		float m_Speed;
		JLHE::Timestep m_FireCooldown;
	};
}