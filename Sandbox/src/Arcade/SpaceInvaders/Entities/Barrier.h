#pragma once
#include "JLHE.h"

namespace Arcade {

	class Barrier : public JLHE::Entity {
	public:
		Barrier(glm::vec3 position, glm::vec2 size);

		void Hit();
	};
}