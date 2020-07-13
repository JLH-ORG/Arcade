#include "Player.h"

namespace Arcade {

	Player::Player(glm::vec3 position, glm::vec2 size, float speed)
		: JLHE::Entity(position, size, 0), m_Speed(speed), m_FireCooldown(1) {}

	void Player::OnUpdate(JLHE::Timestep& ts) {
		if (JLHE::Input::IsKeyPressed(JLHE_KEY_A))
			m_Position.x -= m_Speed * ts;
		else if (JLHE::Input::IsKeyPressed(JLHE_KEY_D))
			m_Position.x += m_Speed * ts;
		if (JLHE::Input::IsKeyPressed(JLHE_KEY_SPACE))
			Fire();
	}

	void Player::Fire() {
		JLHE_INFO("Fired");
	}
}