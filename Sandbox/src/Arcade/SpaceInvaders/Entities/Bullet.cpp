#pragma once

#include "Bullet.h"

namespace Arcade {

	Bullet::Bullet(glm::vec3 position, glm::vec2 size, float velocity) 
		: JLHE::Entity(position, size, 0), m_Velocity(velocity), m_Collided(false), m_Countdown(0.5f) {}

	void Bullet::OnUpdate(JLHE::Timestep& ts) {
		if (!this->m_Collided) { 
			this->m_Position.y += ts * m_Velocity;
		} else {
			this->m_Countdown -= ts;
		}
	}

	void Bullet::Hit() {
		this->m_Collided = true;
		// should change texture here
	}

	bool Bullet::IsHit() {
		return m_Collided;
	}

	bool Bullet::IsDead() {
		return m_Collided && (m_Countdown < 0);
	}

}