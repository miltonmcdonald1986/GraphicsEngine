#pragma once

#include "App.h"

class DemoTransformationsApp final : public App
{
public:
	explicit DemoTransformationsApp(GLFWwindow* pWindow);
	~DemoTransformationsApp() override;
	auto Iterate() -> void override;

private:
	GLFWframebuffersizefun m_pPrevFramebufferSizeCallback = nullptr;
	GraphicsEngine::Entity* m_pEntity = nullptr; 
	GraphicsEngine::ShaderId m_ShaderId = 0;
};
