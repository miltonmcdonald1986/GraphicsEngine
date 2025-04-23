#pragma once

#include "App.h"
#include "fwd.h"

class DemoFlashingGreenTriangleApp : public App
{
public:
	explicit DemoFlashingGreenTriangleApp(GLFWwindow* pWindow);

	auto Iterate() -> void override;

private:
	GraphicsEngine::IUniformPtr m_spUniform;
};
