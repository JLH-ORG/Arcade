#include "SpaceInvadersGame.h"

#include "Entities/Player.h"
#include "Entities/Alien.h"
#include "Entities/Bullet.h"
#include "Entities/Barrier.h"

namespace Arcade {

	bool SpaceInvadersGame::s_ChangeDirections = false;
	bool IsCollision(JLHE::Entity e1, JLHE::Entity e2);
	
	SpaceInvadersGame::SpaceInvadersGame() {
		for (float i = -5; i < 5; i++) {
			for (float j = 0; j < 5; j++) {
				bool canFire = false;
				if (j == 0)
					canFire = true;
				Alien* e = new Alien({ i / 10 , 0.5f + j / 10 , 0 }, { 1.0f / 11.0f, 1.0f / 11.0f }, 0.5f, canFire, m_EntitySystem, m_AlienBullets);
				m_EntitySystem.AddEntity(e) ? JLHE_TRACE("Added alien entity.") : JLHE_ERROR("Could not add alien entity.");
				m_Aliens.push_back(e);
			}
		}
		for (float i = -1.5; i < 2; i++) {
			Barrier* b = new Barrier({ i, -0.5, 0 }, { 0.2f, 0.2f });
			m_EntitySystem.AddEntity(b);
			m_Barriers.push_back(b);
		}
		Player* p = new Player({ 0, -0.9f, 0 }, {0.1f , 0.1f }, 1, m_EntitySystem, m_PlayerBullets);
		m_Player = p;
		m_EntitySystem.AddEntity(p);
	}

	void SpaceInvadersGame::Update(JLHE::Timestep& ts) {
		m_EntitySystem.OnUpdate(ts);
		Alien::s_MoveDown = false;
		if (SpaceInvadersGame::s_ChangeDirections) { Alien::s_MovingRight = !Alien::s_MovingRight; Alien::s_MoveDown = true; s_ChangeDirections = false; }
		RemoveDead();
		DetectCollisions();
	}

	void SpaceInvadersGame::Render() const {
		m_EntitySystem.OnRender();
	}

	void SpaceInvadersGame::DetectCollisions() {

		// Check for alien-player_bullet collisions 
		for (int i = 0; i < m_Aliens.size(); i++) {
			for (int j = 0; j < m_PlayerBullets.size(); j++) {
				// check for entities hit but not dead
				if (!m_Aliens[i]->IsHit() && !m_PlayerBullets[j]->IsHit()) {
					if (IsCollision(*m_Aliens[i], *m_PlayerBullets[j])) {
						m_Aliens[i]->Hit();
						m_PlayerBullets[j]->Hit();
					}
				}
			}
		}
		// Check for alien_bullet collisions
		for (int i = 0; i < m_AlienBullets.size(); i++) {
			// With player_bullets
			for (int j = 0; j < m_PlayerBullets.size(); j++) {
				if (!m_AlienBullets[i]->IsHit() && !m_PlayerBullets[j]->IsHit()) {
					if (IsCollision(*m_AlienBullets[i], *m_PlayerBullets[j])) {
						m_AlienBullets[i]->Hit();
						m_PlayerBullets[j]->Hit();
					}
				}
			}		
			// With the player
			if (IsCollision(*m_AlienBullets[i], *m_Player)) {
				m_AlienBullets[i]->Hit();
				// Game should end here
			}
		}
		// Check for barrier collisions
		for (int i = 0; i < m_Barriers.size(); i++) {
			// With Alien_bullets
			for (int j = 0; j < m_AlienBullets.size(); j++) {
				if (IsCollision(*m_Barriers[i], *m_AlienBullets[j])) {
					m_Barriers[i]->Hit();
					m_AlienBullets[j]->Hit();
				}
			}
			// With player_bullets
			for (int j = 0; j < m_PlayerBullets.size(); j++) {
				if (IsCollision(*m_Barriers[i], *m_PlayerBullets[j])) {
					m_Barriers[i]->Hit();
					m_PlayerBullets[j]->Hit();
				}
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

	static bool IsCollision(JLHE::Entity e1, JLHE::Entity e2) {
		glm::vec3 e1Position = e1.GetPosition(); glm::vec2 e1Size = e1.GetSize();
		glm::vec3 e2Position = e2.GetPosition(); glm::vec2 e2Size = e2.GetSize();

		if ((e1Position.x - e1Size.x / 2 < e2Position.x + e2Size.x / 2) && (e2Position.x + e2Size.x / 2 < e1Position.x + e1Size.x / 2) && (e1Position.y - e1Size.y / 2 < e2Position.y + e2Size.y / 2) && (e2Position.y + e2Size.y / 2 < e1Position.y + e1Size.y / 2))
			return true;
		else if ((e1Position.x - e1Size.x / 2 < e2Position.x - e2Size.x / 2) && (e2Position.x - e2Size.x / 2 < e1Position.x + e1Size.x / 2) && (e1Position.y - e1Size.y / 2 < e2Position.y + e2Size.y / 2) && (e2Position.y + e2Size.y / 2 < e1Position.y + e1Size.y / 2))
			return true;
		else if ((e1Position.x - e1Size.x / 2 < e2Position.x + e2Size.x / 2) && (e2Position.x + e2Size.x / 2 < e1Position.x + e1Size.x / 2) && (e1Position.y - e1Size.y / 2 < e2Position.y - e2Size.y / 2) && (e2Position.y - e2Size.y / 2 < e1Position.y + e1Size.y / 2))
			return true;
		else if ((e1Position.x - e1Size.x / 2 < e2Position.x - e2Size.x / 2) && (e2Position.x - e2Size.x / 2 < e1Position.x + e1Size.x / 2) && (e1Position.y - e1Size.y / 2 < e2Position.y - e2Size.y / 2) && (e2Position.y - e2Size.y / 2 < e1Position.y + e1Size.y / 2))
			return true;
		else
			return false;
	}

}

