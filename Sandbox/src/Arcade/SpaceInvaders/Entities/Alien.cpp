#include "Alien.h"
#include "Arcade/SpaceInvaders/SpaceInvadersGame.h"
#include "Bullet.h"

namespace Arcade {

	bool Alien::s_MovingRight = true;
	bool Alien::s_MoveDown = false;

	// this should be set by the game and depends on window size
	float Alien::s_Bound = 1.75f;

	Alien::Alien(glm::vec3 position, glm::vec2 size, float speed, bool canFire, JLHE::EntitySystem& entitySystem, std::vector<Bullet*>& bullets)
		: JLHE::Entity(position, size, 0), m_Speed(speed), m_IsHit(false), m_Countdown(0.8f), m_CanFire(canFire), m_OccupiedEntitySystem(entitySystem), m_Bullets(bullets), m_FireCooldown(0) {}

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

		if (m_CanFire) {
			m_FireCooldown -= ts;
			Fire();
		}
	}

	void Alien::Hit() {
		m_IsHit = true;
		// Change the texture to dead texture here.
	}

	void Alien::SetCanFire() {
		m_CanFire = true;
	}

	void Alien::Fire() {
		if (m_FireCooldown <= 0 && rand() % 1000 < 1) {
			Bullet* b = new Bullet({ this->m_Position.x, this->m_Position.y, 0 }, { 0.07f, 0.07f }, -0.5f);
			m_OccupiedEntitySystem.AddEntity(b);
			m_Bullets.push_back(b);
			m_FireCooldown = 5;
		}
	}

	bool Alien::IsHit() {
		return this->m_IsHit;
	}

	bool Alien::IsDead() {
		return this->m_IsHit && m_Countdown < 0;
	}

	bool Alien::CanFire() {
		return m_CanFire;
	}

}