#include "Barrier.h"

namespace Arcade {

	Barrier::Barrier(glm::vec3 position, glm::vec2 size) 
		: JLHE::Entity(position, size, 0) {}

	void Barrier::Hit() {}
}