#pragma once
#include "JLHE.h"

namespace Arcade {

	class Bullet : public JLHE::Entity {
	public:
		Bullet(glm::vec3 position, glm::vec2 size, float velocity);
		
		virtual void OnUpdate(JLHE::Timestep& ts) override;
		void Hit();
	private:
		float m_Velocity;
		bool m_Collided;
		float m_Timeout;
	};

}