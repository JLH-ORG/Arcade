#include "Alien.h"

namespace Arcade {
	bool Alien::s_MovingRight = true;
	float Alien::s_Bound = 1.0f;

	Alien::Alien(glm::vec3 position, glm::vec2 size, float speed) 
		: JLHE::Entity(position, size, 0), m_Speed(speed), m_IsDead(false) {}

	void Alien::OnUpdate(JLHE::Timestep& ts) {
		if (Alien::s_MovingRight) {
			m_Position.x += ts * m_Speed;
			if (m_Position.x > Alien::s_Bound)
				Alien::s_MovingRight = false;
		}
		else
		{
			m_Position.x -= ts * m_Speed;
			if (m_Position.x < Alien::s_Bound)
				Alien::s_MovingRight = true;
		}
	}

	void Alien::Die() {

	}

	bool Alien::IsHit() {
		return false;
	}

	void Alien::Move() {
		
	}
}