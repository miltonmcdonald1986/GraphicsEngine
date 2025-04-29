#pragma once

#include "App.h"

class TestApp : public App
{
public:
	explicit TestApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;

private:
	GLFWframebuffersizefun m_pPrevFramebufferSizeCallback = nullptr;
};
