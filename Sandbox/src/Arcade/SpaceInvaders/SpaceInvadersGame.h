#pragma once

#include "JLHE.h"
#include "Arcade/Game.h"

namespace Arcade {

	class SpaceInvadersGame : public Game {
	public:
		SpaceInvadersGame();

		virtual void Render() const override;
		virtual void Update(JLHE::Timestep& ts) override;
	public:
		static bool s_ChangeDirections;         
	private:
		//why do I need mutable?
		mutable JLHE::EntitySystem m_EntitySystem;
	};

}