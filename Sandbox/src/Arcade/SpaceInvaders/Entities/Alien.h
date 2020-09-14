#pragma once
#include "JLHE.h"

namespace Arcade {
	
	class Bullet;

	class Alien : public JLHE::Entity {
	public:
		Alien(glm::vec3 position, glm::vec2 size, float speed, bool canFire, JLHE::EntitySystem& entitySystem, std::vector<Bullet*>& bullets);

		virtual void OnUpdate(JLHE::Timestep& ts) override;

		void Hit();
		void SetCanFire();
		
		bool IsHit();
		bool IsDead();
		bool CanFire();
	public:
		static bool s_MovingRight;
		static bool s_MoveDown;

		void Fire();
	private:
		static float s_Bound;

		bool m_IsHit;
		bool m_CanFire;
		float m_Speed;
		float m_Countdown;
		float m_FireCooldown;
		JLHE::EntitySystem& m_OccupiedEntitySystem;
		std::vector<Bullet*>& m_Bullets;
	private:

	};


}
