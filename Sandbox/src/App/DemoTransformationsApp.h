#pragma once

#include "App.h"

#include "fwd.h"

class DemoTransformationsApp : public App
{
public:
	explicit DemoTransformationsApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;

private:
	GraphicsEngine::IShaderPtr m_spShader = nullptr;
};
