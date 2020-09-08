#pragma once
#include "JLHE.h"

namespace Arcade {
	class Alien : public JLHE::Entity {
	public:
		Alien(glm::vec3 position, glm::vec2 size, float speed);

		virtual void OnUpdate(JLHE::Timestep& ts) override;

		void Die();	

		

	private:
		float m_Speed;
		bool m_IsDead;

		static bool s_MovingRight;
		static float s_Bound;

		bool IsHit();
		void Move();
	};


}