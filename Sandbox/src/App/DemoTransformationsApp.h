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
	graphics_engine::Entity* m_pEntity = nullptr;
};
