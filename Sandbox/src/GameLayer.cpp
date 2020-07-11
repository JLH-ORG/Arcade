#include "GameLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

namespace Arcade {

	GameLayer::GameLayer() 
		: Layer("GameLayer"), m_CameraController(1280.0f / 720.0f, false) {}

	void GameLayer::OnAttach() {
		JLHE_PROFILE_FUNCTION();
		m_Game = Game::Create();
	}

	void GameLayer::OnDetach() {
		JLHE_PROFILE_FUNCTION();
	}

	void GameLayer::OnUpdate(JLHE::Timestep ts) {
		JLHE_PROFILE_FUNCTION();

		JLHE::Renderer2D::ResetStats();
		m_CameraController.OnUpdate(ts);

		JLHE::RenderCommand::SetClearColour({ 1.0f, 0.1f, 0.1f, 1.0f });
		JLHE::RenderCommand::Clear();

		// Render here --->
		JLHE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		m_Game->Render();
		JLHE::Renderer2D::EndScene();
		// ----------------

	}

	void GameLayer::OnImGuiRender() {
        JLHE_PROFILE_FUNCTION();

	}

	void GameLayer::OnEvent(JLHE::Event& e) {
		m_CameraController.OnEvent(e);
	}

}