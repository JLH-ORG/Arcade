#include "Alien.h"
#include "Arcade/SpaceInvaders/SpaceInvadersGame.h"

namespace Arcade {

	bool Alien::s_MovingRight = true;
	bool Alien::s_MoveDown = false;

	// this should be set by the game and depends on window size
	float Alien::s_Bound = 1.75f;

	Alien::Alien(glm::vec3 position, glm::vec2 size, float speed) 
		: JLHE::Entity(position, size, 0), m_Speed(speed), m_IsHit(false), m_Countdown(0.8f) {}

	void Alien::OnUpdate(JLHE::Timestep& ts) {

		if (m_IsHit) {
			m_Countdown -= ts;
		}

		if (s_MoveDown) { m_Position.y -= 0.05f; }

		if (Alien::s_MovingRight) {
			m_Position.x += ts * m_Speed;
			if (m_Position.x > Alien::s_Bound) { SpaceInvadersGame::s_ChangeDirections = true; }
		}
		else {
			m_Position.x -= ts * m_Speed;
			if (m_Position.x < -Alien::s_Bound) { SpaceInvadersGame::s_ChangeDirections = true; }
		}

	}

	void Alien::Hit() {
		m_IsHit = true;
		// Change the texture to dead texture here.
	}

	bool Alien::IsHit() {
		return this->m_IsHit;
	}

	bool Alien::IsDead() {
		return this->m_IsHit && m_Countdown < 0;
	}

}