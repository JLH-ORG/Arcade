#include "SpaceInvadersGame.h"

#include "Entities/Player.h"
#include "Entities/Alien.h"
#include "Entities/Bullet.h"

namespace Arcade {

	bool SpaceInvadersGame::s_ChangeDirections = false;
	
	SpaceInvadersGame::SpaceInvadersGame() {
		for (float i = -5; i < 5; i++) {
			for (float j = 0; j < 5; j++) {
				bool canFire = false;
				if (j == 0)
					canFire = true;
				Alien* e = new Alien({ i / 10 , j / 10 , 0 }, { 1.0f / 11.0f, 1.0f / 11.0f }, 0.5f, canFire, m_EntitySystem, m_AlienBullets);
				m_EntitySystem.AddEntity(e) ? JLHE_TRACE("Added alien entity.") : JLHE_ERROR("Could not add alien entity.");
				m_Aliens.push_back(e);
			}
		}
		Player* p = new Player({ 0, -0.5f, 0 }, {0.1f , 0.1f }, 1, m_EntitySystem, m_PlayerBullets);
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
			for (int j = 0; j < m_PlayerBullets.size(); j++) {
				// check for entities hit but not dead
				if (!m_Aliens[i]->IsHit() && !m_PlayerBullets[j]->IsHit()) {
					glm::vec3 alienPos = m_Aliens[i]->GetPosition(); glm::vec2 alienSize = m_Aliens[i]->GetSize();
					glm::vec3 bulletPos = m_PlayerBullets[j]->GetPosition(); glm::vec2 bulletSize = m_PlayerBullets[j]->GetSize();
		
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
						m_PlayerBullets[j]->Hit();
					}
				}
			}
		}

		for (int i = 0; i < m_AlienBullets.size(); i++) {
			glm::vec3 alienBulletPos = m_AlienBullets[i]->GetPosition(); glm::vec2 alienSize  = m_AlienBullets[i]->GetSize();
			bool hit = false;
			for (int j = 0; j < m_PlayerBullets.size(); j++) {
				glm::vec3 playerBulletPos = m_PlayerBullets[j]->GetPosition(); glm::vec2 playerBulletSize = m_PlayerBullets[j]->GetSize();

				if ((playerBulletPos.x - playerBulletSize.x / 2 < alienBulletPos.x + alienSize.x / 2) && (alienBulletPos.x + alienSize.x / 2 < playerBulletPos.x + playerBulletSize.x / 2) && (playerBulletPos.y - playerBulletSize.y / 2 < alienBulletPos.y + alienSize.y / 2) && (alienBulletPos.y + alienSize.y / 2 < playerBulletPos.y + playerBulletSize.y / 2))
					hit = true;
				else if ((playerBulletPos.x - playerBulletSize.x / 2 < alienBulletPos.x - alienSize.x / 2) && (alienBulletPos.x - alienSize.x / 2 < playerBulletPos.x + playerBulletSize.x / 2) && (playerBulletPos.y - playerBulletSize.y / 2 < alienBulletPos.y + alienSize.y / 2) && (alienBulletPos.y + alienSize.y / 2 < playerBulletPos.y + playerBulletSize.y / 2))
					hit = true;
				else if ((playerBulletPos.x - playerBulletSize.x / 2 < alienBulletPos.x + alienSize.x / 2) && (alienBulletPos.x + alienSize.x / 2 < playerBulletPos.x + playerBulletSize.x / 2) && (playerBulletPos.y - playerBulletSize.y / 2 < alienBulletPos.y - alienSize.y / 2) && (alienBulletPos.y - alienSize.y / 2 < playerBulletPos.y + playerBulletSize.y / 2))
					hit = true;
				else if ((playerBulletPos.x - playerBulletSize.x / 2 < alienBulletPos.x - alienSize.x / 2) && (alienBulletPos.x - alienSize.x / 2 < playerBulletPos.x + playerBulletSize.x / 2) && (playerBulletPos.y - playerBulletSize.y / 2 < alienBulletPos.y - alienSize.y / 2) && (alienBulletPos.y - alienSize.y / 2 < playerBulletPos.y + playerBulletSize.y / 2))
					hit = true;
				if (hit) {
					m_AlienBullets[i]->Hit();
					m_PlayerBullets[j]->Hit();
				}
			}
			glm::vec3 playerPos = m_Player->GetPosition(); glm::vec2 playerSize = m_Player->GetSize();
			if ((playerPos.x - playerSize.x / 2 < alienBulletPos.x + alienSize.x / 2) && (alienBulletPos.x + alienSize.x / 2 < playerPos.x + playerSize.x / 2) && (playerPos.y - playerSize.y / 2 < alienBulletPos.y + alienSize.y / 2) && (alienBulletPos.y + alienSize.y / 2 < playerPos.y + playerSize.y / 2))
				hit = true;
			else if ((playerPos.x - playerSize.x / 2 < alienBulletPos.x - alienSize.x / 2) && (alienBulletPos.x - alienSize.x / 2 < playerPos.x + playerSize.x / 2) && (playerPos.y - playerSize.y / 2 < alienBulletPos.y + alienSize.y / 2) && (alienBulletPos.y + alienSize.y / 2 < playerPos.y + playerSize.y / 2))
				hit = true;
			else if ((playerPos.x - playerSize.x / 2 < alienBulletPos.x + alienSize.x / 2) && (alienBulletPos.x + alienSize.x / 2 < playerPos.x + playerSize.x / 2) && (playerPos.y - playerSize.y / 2 < alienBulletPos.y - alienSize.y / 2) && (alienBulletPos.y - alienSize.y / 2 < playerPos.y + playerSize.y / 2))
				hit = true;
			else if ((playerPos.x - playerSize.x / 2 < alienBulletPos.x - alienSize.x / 2) && (alienBulletPos.x - alienSize.x / 2 < playerPos.x + playerSize.x / 2) && (playerPos.y - playerSize.y / 2 < alienBulletPos.y - alienSize.y / 2) && (alienBulletPos.y - alienSize.y / 2 < playerPos.y + playerSize.y / 2))
				hit = true;
			if (hit) {
				m_AlienBullets[i]->Hit();
				// Game should end here
			}


		}
		
	}


	void SpaceInvadersGame::RemoveDead() {

		for (int i = 0; i < m_Aliens.size(); i++) {
			if (m_Aliens[i]->IsDead()) {
				if (i + 1 < m_Aliens.size() && m_Aliens[i]->CanFire()) 
					m_Aliens[i + 1]->SetCanFire();
				m_EntitySystem.RemoveEntity(m_Aliens[i]);
				m_Aliens.erase(m_Aliens.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < m_PlayerBullets.size(); i++) {
			if (m_PlayerBullets[i]->IsDead()) {
				m_EntitySystem.RemoveEntity(m_PlayerBullets[i]);
				m_PlayerBullets.erase(m_PlayerBullets.begin() + i);
				i--;
			}	
		}

		for (int i = 0; i < m_AlienBullets.size(); i++) {
			if (m_AlienBullets[i]->IsDead()) {
				m_EntitySystem.RemoveEntity(m_AlienBullets[i]);
				m_AlienBullets.erase(m_AlienBullets.begin() + i);
				i--;
			}
		}
	
	}

}

