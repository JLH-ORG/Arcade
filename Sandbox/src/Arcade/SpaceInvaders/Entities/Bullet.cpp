#pragma once

#include "Bullet.h"

namespace Arcade {

	Bullet::Bullet(glm::vec3 position, glm::vec2 size, float velocity) 
		: JLHE::Entity(position, size, 0), m_Velocity(velocity) {}

	void Bullet::OnUpdate(JLHE::Timestep& ts) {
		this->m_Position.y += ts * m_Velocity;
	}

	void Bullet::Hit() {

	}

}