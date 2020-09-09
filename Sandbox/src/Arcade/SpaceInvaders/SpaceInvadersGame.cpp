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
				m_EntitySystem.AddEntity(e);
			}
		}
		Player* p = new Player({ 0, -0.5f, 0 }, {0.1f , 0.1f }, 1, m_EntitySystem);
		m_EntitySystem.AddEntity(p);

	}

	void SpaceInvadersGame::Update(JLHE::Timestep& ts) {
		m_EntitySystem.OnUpdate(ts);
		if (SpaceInvadersGame::s_ChangeDirections) { Alien::s_MovingRight = !Alien::s_MovingRight; s_ChangeDirections = false;  }
	}

	void SpaceInvadersGame::Render() const {
		m_EntitySystem.OnRender();
	}

}

