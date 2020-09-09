#pragma once
#include "JLHE.h"

namespace Arcade {
	class Alien : public JLHE::Entity {
	public:
		Alien(glm::vec3 position, glm::vec2 size, float speed);

		virtual void OnUpdate(JLHE::Timestep& ts) override;
		void Die();
	public:
		static bool s_MovingRight;
	private:
		static float s_Bound;

		float m_Speed;
		bool m_IsDead;
	private:
		bool IsHit();
	};


}
