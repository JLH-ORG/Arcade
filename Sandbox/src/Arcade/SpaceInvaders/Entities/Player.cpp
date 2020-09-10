#include "Player.h"
#include "Bullet.h"

namespace Arcade {

	Player::Player(glm::vec3 position, glm::vec2 size, float speed, JLHE::EntitySystem& entitySystem, std::vector<Bullet*>& bullets)
		: JLHE::Entity(position, size, 0), m_Speed(speed), m_FireCooldown(1), m_OccupiedEntitySystem(entitySystem), m_Bullets(bullets) {}

	void Player::OnUpdate(JLHE::Timestep& ts) {
		if (JLHE::Input::IsKeyPressed(JLHE_KEY_A))
			m_Position.x -= m_Speed * ts;
		else if (JLHE::Input::IsKeyPressed(JLHE_KEY_D))
			m_Position.x += m_Speed * ts;
		if (JLHE::Input::IsKeyPressed(JLHE_KEY_SPACE))
			Fire();
	}

	void Player::Fire() {
		Bullet* b = new Bullet({ this->m_Position.x, this->m_Position.y, 0 }, { 0.07f, 0.07f }, 0.5f);
		m_OccupiedEntitySystem.AddEntity(b);
		m_Bullets.push_back(b);
  		JLHE_INFO("Fired");
	}

}