#include "SpaceInvadersGame.h"

namespace Arcade {
	
	SpaceInvadersGame::SpaceInvadersGame() {
		for (float i = -5; i < 5; i++) {
			for (float j = 0; j < 5; j++) {
				JLHE::Entity e({ i / 10 , j / 10 , 0 }, { 1.0f / 11.0f, 1.0f / 11.0f }, 0);
				m_EntitySystem.AddEntity(e);
			}
		}
	}

	void SpaceInvadersGame::Render() const {
		m_EntitySystem.OnRender();
	}
}

