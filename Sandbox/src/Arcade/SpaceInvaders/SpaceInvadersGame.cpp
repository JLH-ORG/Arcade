#include "SpaceInvadersGame.h"

#include "Entities/Player.h"
#include "Entities/Alien.h"
#include "Entities/Bullet.h"

namespace Arcade {

	bool SpaceInvadersGame::s_ChangeDirections = false;
	
	SpaceInvadersGame::SpaceInvadersGame() {
		for (float i = -5; i < 5; i++) {
			for (float j = 0; j < 5; j++) {
				Alien* e = new Alien({ i / 10 , j / 10 , 0 }, { 1.0f / 11.0f, 1.0f / 11.0f }, 0.5f);
				m_EntitySystem.AddEntity(e) ? JLHE_TRACE("Added alien entity.") : JLHE_ERROR("Could not add alien entity.");
				m_Aliens.push_back(e);
			}
		}
		Player* p = new Player({ 0, -0.5f, 0 }, {0.1f , 0.1f }, 1, m_EntitySystem, m_Bullets);
		m_Player = p;
		m_EntitySystem.AddEntity(p);

	}

	void SpaceInvadersGame::Update(JLHE::Timestep& ts) {
		m_EntitySystem.OnUpdate(ts);
		Alien::s_MoveDown = false;
		if (SpaceInvadersGame::s_ChangeDirections) { Alien::s_MovingRight = !Alien::s_MovingRight; Alien::s_MoveDown = true; s_ChangeDirections = false; }
		DetectCollisions();

	}

	void SpaceInvadersGame::Render() const {
		m_EntitySystem.OnRender();
	}

	void SpaceInvadersGame::DetectCollisions() {

		for (auto& alien : m_Aliens) {
			for (auto& bullet : m_Bullets) {
				glm::vec3 alienPos = alien->GetPosition(); glm::vec2 alienSize = alien->GetSize();
				glm::vec3 bulletPos = bullet->GetPosition(); glm::vec2 bulletSize = bullet->GetSize();

				bool hit = false;

				if ((alienPos.x - alienSize.x / 2 < bulletPos.x + bulletSize.x / 2) && (bulletPos.x + bulletSize.x / 2 < alienPos.x + alienSize.x / 2) && (alienPos.y - alienSize.y / 2 < bulletPos.y + bulletSize.y / 2) && (bulletPos.y + bulletSize.y / 2 < alienPos.y + alienSize.y / 2))
					hit = true;
				else if ((alienPos.x - alienSize.x / 2 < bulletPos.x - bulletSize.x / 2) && (bulletPos.x - bulletSize.x / 2 < alienPos.x + alienSize.x / 2) && (alienPos.y - alienSize.y / 2 < bulletPos.y + bulletSize.y / 2) && (bulletPos.y + bulletSize.y / 2 < alienPos.y + alienSize.y / 2))
					hit = true;
				else if ((alienPos.x - alienSize.x / 2 < bulletPos.x + bulletSize.x / 2) && (bulletPos.x + bulletSize.x / 2 < alienPos.x + alienSize.x / 2) && (alienPos.y - alienSize.y / 2 < bulletPos.y - bulletSize.y / 2) && (bulletPos.y - bulletSize.y / 2 < alienPos.y + alienSize.y / 2))
					hit = true;
				else if ((alienPos.x - alienSize.x / 2 < bulletPos.x - bulletSize.x / 2) && (bulletPos.x - bulletSize.x / 2 < alienPos.x + alienSize.x / 2) && (alienPos.y - alienSize.y / 2 < bulletPos.y - bulletSize.y / 2) && (bulletPos.y - bulletSize.y / 2 < alienPos.y + alienSize.y / 2))
					hit = true;
				if (hit) {
					alien->Die();
					bullet->Hit();
				}
				
			}
		}

	}

	void SpaceInvadersGame::RemoveDead() {
		for (auto& alien : m_Aliens) {
			if (alien->IsDead()) {
				m_EntitySystem.RemoveEntity(alien);
			}
		}

	}

}

