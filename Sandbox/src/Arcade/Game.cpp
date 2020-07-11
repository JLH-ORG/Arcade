#include "Game.h"

#include "SpaceInvaders/SpaceInvadersGame.h"

namespace Arcade {

	JLHE::Ref<Game> Game::Create() {
		switch (Game::GameMode) {
			case Mode::SpaceInvaders: return JLHE::CreateRef<SpaceInvadersGame>();
		}
	}
}