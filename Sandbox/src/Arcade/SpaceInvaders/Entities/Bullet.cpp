#pragma once

#include "Bullet.h"

namespace Arcade {

	Bullet::Bullet(glm::vec3 position, glm::vec2 size, float velocity) 
		: JLHE::Entity(position, size, 0), m_Velocity(velocity) {}

	void Bullet::OnUpdate(JLHE::Timestep& ts) {
		if (!this->m_Collided) { 
			this->m_Position.y += ts * m_Velocity;
		} else {
			this->m_Timeout -= ts;
		}
	}

	void Bullet::Hit() {
		this->m_Collided = true; this->m_Timeout = 0.5f;
	}

}