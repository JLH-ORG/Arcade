#include <JLHE.h>
#include <JLHE/Core/EntryPoint.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include "GameLayer.h"

#include <imgui/imgui.h>

class Sandbox : public JLHE::Application {
public:
	Sandbox() {
		PushLayer(new Arcade::GameLayer());
	}

	~Sandbox() {

	}

};

JLHE::Application* JLHE::CreateApplication() {
	return new Sandbox();
}