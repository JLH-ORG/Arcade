#pragma once

#include <JLHE.h>

#include "Arcade/Game.h"

namespace Arcade {

	class GameLayer : public JLHE::Layer {
	public:
		GameLayer();
		virtual ~GameLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(JLHE::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(JLHE::Event& e) override;
	private:
		JLHE::Ref<Arcade::Game> m_Game;
	private:
		JLHE::OrthographicCameraController m_CameraController;
	};

}