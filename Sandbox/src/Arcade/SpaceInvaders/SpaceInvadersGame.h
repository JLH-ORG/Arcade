#pragma once

#include "JLHE.h"
#include "Arcade/Game.h"

namespace Arcade {

	class SpaceInvadersGame : public Game {
	public:
		SpaceInvadersGame();

		virtual void Render() const override;

	private:
		//why do I need mutable?
		mutable JLHE::EntitySystem m_EntitySystem;
	};

}