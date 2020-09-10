#pragma once

#include "JLHE.h"
#include "Arcade/Game.h"

namespace Arcade {

	class Player;
	class Alien;
	class Bullet;

	class SpaceInvadersGame : public Game {
	public:
		SpaceInvadersGame();

		virtual void Render() const override;
		virtual void Update(JLHE::Timestep& ts) override;
	public:
		static bool s_ChangeDirections;
	private:
		void DetectCollisions();
	private:
		mutable JLHE::EntitySystem m_EntitySystem;
		Player* m_Player;
		std::vector<Alien*> m_Aliens;
		std::vector<Bullet*> m_Bullets;
	};

}