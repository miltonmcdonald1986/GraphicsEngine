#pragma once

#include "App.h"

class DemoFlashingGreenTriangleApp : public App
{
public:
	DemoFlashingGreenTriangleApp(GLFWwindow* pWindow);

	virtual auto Iterate() -> void override;

private:
	GraphicsEngine::IUniformPtr m_spUniform;
};
