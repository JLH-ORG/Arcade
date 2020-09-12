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
		RemoveDead();
	}

	void SpaceInvadersGame::Render() const {
		m_EntitySystem.OnRender();
	}

	void SpaceInvadersGame::DetectCollisions() {

		for (int i = 0; i < m_Aliens.size(); i++) {
			for (int j = 0; j < m_Bullets.size(); j++) {
				// check for entities hit but not dead
				if (!m_Aliens[i]->IsHit() && !m_Bullets[j]->IsHit()) {
					glm::vec3 alienPos = m_Aliens[i]->GetPosition(); glm::vec2 alienSize = m_Aliens[i]->GetSize();
					glm::vec3 bulletPos = m_Bullets[j]->GetPosition(); glm::vec2 bulletSize = m_Bullets[j]->GetSize();
		
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
						m_Aliens[i]->Hit();
						m_Bullets[j]->Hit();
					}
				}
			}
		}
	}


	void SpaceInvadersGame::RemoveDead() {
		for (int i = 0; i < m_Aliens.size(); i++) {
			if (m_Aliens[i]->IsDead()) {
				m_EntitySystem.RemoveEntity(m_Aliens[i]);
				m_Aliens.erase(m_Aliens.begin() + i);
			}
		}
		for (int i = 0; i < m_Bullets.size(); i++) {
			if (m_Bullets[i]->IsDead()) {
				m_EntitySystem.RemoveEntity(m_Bullets[i]);
				m_Bullets.erase(m_Bullets.begin() + i);
			}
		}
	
	}

}

