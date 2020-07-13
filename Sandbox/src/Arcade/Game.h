#pragma once

#include "JLHE.h"
#include "Arcade/Mode.h"

namespace Arcade {

	class Game {
	public:
		virtual void Render() const = 0;
		virtual void Update(JLHE::Timestep& ts) = 0;

		static JLHE::Ref<Game> Create();
	public:

		//should not be const
		static const Mode GameMode = Mode::SpaceInvaders;
	};

}