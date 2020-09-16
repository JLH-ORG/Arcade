#pragma once

#include "JLHE.h"
#include "Arcade/Game.h"

namespace Arcade {

	class Player;
	class Alien;
	class Bullet;
	class Barrier;

	class SpaceInvadersGame : public Game {
	public:
		SpaceInvadersGame();

		virtual void Render() const override;
		virtual void Update(JLHE::Timestep& ts) override;
	public:
		static bool s_ChangeDirections;
	private:
		void DetectCollisions();
		void RemoveDead();
	private:
		mutable JLHE::EntitySystem m_EntitySystem;
		Player* m_Player;
		std::vector<Alien*> m_Aliens;
		std::vector<Bullet*> m_PlayerBullets;
		std::vector<Bullet*> m_AlienBullets;
		std::vector<Barrier*> m_Barriers;
	};

}