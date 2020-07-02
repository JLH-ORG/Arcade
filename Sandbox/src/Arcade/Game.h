#pragma once

#include "Arcade/Mode.h"

namespace Arcade {

	class Game {
	public:
		virtual void Render() const = 0;
	public:
		Mode GameMode;
	};

}