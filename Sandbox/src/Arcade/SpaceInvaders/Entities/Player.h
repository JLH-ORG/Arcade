#pragma once
#include "JLHE.h"

namespace Arcade {

	class Player : public JLHE::Entity {
	public:
		Player(glm::vec3 position, glm::vec2 size, float speed);

		virtual void OnUpdate(JLHE::Timestep& ts) override;

		void Fire();

	private:
		float m_Speed;
		JLHE::Timestep m_FireCooldown;
	};
}